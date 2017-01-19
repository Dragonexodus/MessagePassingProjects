#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>

static const int RETURN_COUNT = 5;
static const int INVALID_VALUE = -1;
static const int MASTER = 0;
using namespace std;

void printFromMaster(int rank, string message, ostream &outputStream);

void printFromMaster(int rank, double message, ostream &outputStream);

void parallelSearch(int p, int rank, RectangleDetector &detector, const short *matrix, int n);

void summarize(int p, int rank, RectangleDetector &detector, RectangleValidator &validator, const int *mainResult);

int summarizeRes(int p, const RectangleDetector &detector, const int *mainResult, vector<int> &members);

int checkPositions(const RectangleDetector &detector, const int *mainResult, vector<int> &members, int res);

int main(int argc, char **argv) {
    int p;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    if (p % 2 == 1 && p > 1) {
        printFromMaster(rank, "Anzahl der Prozessoren muss gerade sein!", cerr);
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    RectangleDetector detector = RectangleDetector();
    double startTime = MPI_Wtime();

    short *matrix = NULL;
    int n = 0;

    if (rank == MASTER) {
        std::string configFile = "config";

        if (argc > 1) {
            configFile = argv[1];
        }
        pair<short *, int> result = detector.readFile(configFile.c_str());
        if (result.second != INVALID_VALUE) {
            n = result.second;
            matrix = result.first;
            if (n % p != 0) {
                n = -1;
            }
        }
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (n < 0) {
        if (n == -1) {
            printFromMaster(rank, "Anzahl der Zeilen nicht teilbar durch die Prozessor-Anzahl!", cerr);
        } else if (n == -2) {
            printFromMaster(rank, "Konnte config-File nicht lesen.", cerr);
        }
        if (matrix != NULL) {
            delete matrix;
        }
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    if (p == 1) {
        const pair<int, RectangleValidator> &detectorResult = detector.search(matrix, n, n);
        detector.printResult(detectorResult.first);
        if (detectorResult.first == detector.RECT_FOUND) {
            //cout << detectorResult.second << endl;
        }
        if (matrix != NULL) {
            delete matrix;
        }
    } else {
        parallelSearch(p, rank, detector, matrix, n);
    }
    double stopTime = MPI_Wtime();
    printFromMaster(rank, stopTime - startTime, cout);

    MPI_Finalize();

    return EXIT_SUCCESS;
}

void parallelSearch(int p, int rank, RectangleDetector &detector, const short *matrix, int n) {
    int localN = n / p;
    int localSize = localN * n;
    short *localMatrix = new short[localSize];

    MPI_Scatter(matrix, localSize, MPI_SHORT, localMatrix, localSize, MPI_SHORT, 0, MPI_COMM_WORLD);
    if (rank == MASTER && matrix != NULL) {
        delete matrix;
    }
    const pair<int, RectangleValidator> &detectorResult = detector.search(localMatrix, n, localN);
    RectangleValidator validator = detectorResult.second;

    int *localResult = new int[RETURN_COUNT];
    localResult[0] = detectorResult.first;
    localResult[1] = validator.getStartX();
    localResult[2] = validator.getStopX();
    localResult[3] = validator.getStartY() + localN * rank;
    localResult[4] = validator.getStopY() + localN * rank;
    int *mainResult = new int[RETURN_COUNT * p];
    MPI_Gather(localResult, RETURN_COUNT, MPI_INT, mainResult, RETURN_COUNT, MPI_INT, 0, MPI_COMM_WORLD);

    summarize(p, rank, detector, validator, mainResult);

    delete localMatrix;
    delete localResult;
    delete mainResult;
}

void summarize(int p, int rank, RectangleDetector &detector, RectangleValidator &validator, const int *mainResult) {
    if (rank == MASTER) {
        vector<int> processesWithRect;
        int res = summarizeRes(p, detector, mainResult, processesWithRect);
        res = checkPositions(detector, mainResult, processesWithRect, res);
        detector.printResult(res);
        if (res == detector.RECT_FOUND) {
            validator.setStart(make_pair(mainResult[1 + processesWithRect.front() * RETURN_COUNT],
                                         mainResult[3 + processesWithRect.front() * RETURN_COUNT]));
            validator.setStop(make_pair(mainResult[2 + processesWithRect.back() * RETURN_COUNT],
                                        mainResult[4 + processesWithRect.back() * RETURN_COUNT]));
            //cout << validator << endl << endl;
        }
    }
}

int summarizeRes(int p, const RectangleDetector &detector, const int *mainResult, vector<int> &members) {
    int res = detector.NO_RECT;
    members = vector<int>();
    for (int i = 0; i < p; i++) {
        int localRes = mainResult[0 + i * RETURN_COUNT];

        if (localRes == detector.MISMATCH_FOUND) {
            return detector.MISMATCH_FOUND;
        }

        if (i == 0) {
            res = localRes;
            if (localRes == detector.RECT_FOUND) {
                members.push_back(i);
            }
        } else if (localRes == detector.RECT_FOUND) {
            if (members.size() != 0 && members.back() != i - 1) {
                return detector.MISMATCH_FOUND;
            }
            members.push_back(i);
            if (res == detector.NO_RECT) {
                res = localRes;
            }
        }
    }
    return res;
}

int checkPositions(const RectangleDetector &detector, const int *mainResult, vector<int> &members, int res) {
    if (res == detector.RECT_FOUND) {
        int endY = -1;
        int beginX = -1;
        int endX = -1;
        for (auto it = members.begin(); it != members.end(); ++it) {
            int startX = mainResult[1 + *it * RETURN_COUNT];
            int stopX = mainResult[2 + *it * RETURN_COUNT];
            int startY = mainResult[3 + *it * RETURN_COUNT];
            int stopY = mainResult[4 + *it * RETURN_COUNT];
            if (it == members.begin()) {
                endY = stopY;
                beginX = startX;
                endX = stopX;
            } else {
                if (endX != stopX || beginX != startX || endY != startY - 1) {
                    //cout << "closedRect" << endl;
                    res = detector.MISMATCH_FOUND;
                    break;
                }
                endY = stopY;
            }
        }
    }
    return res;
}

void printFromMaster(int rank, string message, ostream &outputStream) {
    if (rank == MASTER) {
        outputStream << message << endl;
    }
}

void printFromMaster(int rank, double message, ostream &outputStream) {
    if (rank == MASTER) {
        outputStream << message << endl;
        //"T(" << n << ") = " << stopTime - startTime << " s" << endl;
        //"----------------------------------------------" << endl << endl;
    }
}
