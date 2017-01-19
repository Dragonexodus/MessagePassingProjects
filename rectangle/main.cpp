#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>

static const int RETURN_COUNT = 5;
using namespace std;

int main(int argc, char **argv) {
    const int MASTER = 0;
    int p;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    if (p % 2 == 1 && p > 1) {
        MPI_Finalize();
        if (rank == MASTER) {
            cerr << "Anzahl der Prozessoren muss gerade sein!" << endl;
        }
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

        n = result.second;
        matrix = result.first;
        if (n % p != 0) {
            n = -1;
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (n == -1) {
        if (rank == MASTER) {
            cout << "Anzahl der Zeilen nicht teilbar durch die Prozessor-Anzahl!" << endl;
        }
        MPI_Finalize();
        return EXIT_SUCCESS;
    }

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

    if (rank == MASTER) {
        //validate res
        int res = detector.NO_RECT;
        vector<int> members = vector<int>();
        for (int i = 0; i < p; i++) {
            int localRes = mainResult[0 + i * RETURN_COUNT];

            if (localRes == detector.MISMATCH_FOUND) {
                res = detector.MISMATCH_FOUND;
                break;
            }

            if (i == 0) {
                res = localRes;
                if (localRes == detector.RECT_FOUND) {
                    members.push_back(i);
                }
            } else if (localRes == detector.RECT_FOUND) {
                if (members.size() != 0 && members.back() != i - 1) {
                    res = detector.MISMATCH_FOUND;
                    break;
                }
                members.push_back(i);
                if (res == detector.NO_RECT) {
                    res = localRes;
                }
            }
        }

//check the validation of the rectangle
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
        detector.printResult(res);
        if (res == detector.RECT_FOUND) {
            validator.setStart(make_pair(mainResult[1 + members.front() * RETURN_COUNT],
                                         mainResult[3 + members.front() * RETURN_COUNT]));
            validator.setStop(make_pair(mainResult[2 + members.back() * RETURN_COUNT],
                                        mainResult[4 + members.back() * RETURN_COUNT]));
            //cout << validator << endl << endl;
        }
    }
    double stopTime = MPI_Wtime();
    if (rank == MASTER) {
        cout << stopTime - startTime << endl;
        //cout << "T(" << n << ") = " << stopTime - startTime << " s" << endl;
        //cout << "----------------------------------------------" << endl << endl;
    }
    delete localMatrix;
    delete localResult;
    delete mainResult;
    MPI_Finalize();

    return EXIT_SUCCESS;
}
