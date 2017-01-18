#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>


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
    //double startTimer = MPI_Wtime();

    int *matrix = NULL;
    int n = 0;
    if (rank == MASTER) {
        pair<int *, int> result = detector.readFile("config");

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
    int *localMatrix = new int[localSize];

    MPI_Scatter(matrix, localSize, MPI_INT, localMatrix, localSize, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == MASTER && matrix != NULL) {
        delete matrix;
    }
    detector.printOldMatrix(localMatrix, localN, n);
    const pair<int, RectangleValidator> &detectorResult = detector.search(localMatrix, n, localN);
    RectangleValidator validator = detectorResult.second;
    if (detectorResult.first == detector.MISMATCH_FOUND) {
        cout << "Found some black fields, but no black rectangle!" << endl << endl;;
    } else if (detectorResult.first == detector.NO_RECT) {
        cout << "No black fields found!" << endl << endl;
    } else {
        cout << "rectangle found: " << validator << endl << endl;
    }

    int *localResult = new int[5];
    localResult[0] = detectorResult.first;
    localResult[1] = validator.getStartX() + localN * rank;
    localResult[2] = validator.getStopX() + localN * rank;
    localResult[3] = validator.getStartY() + localN * rank;
    localResult[4] = validator.getStopX() + localN * rank;
    int *mainResult = new int[5 * p];
    MPI_Gather(localResult, 5, MPI_INT, mainResult, 5, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == MASTER) {
        //validate res
        int res = -1;
        vector<int> members = vector<int>();
        for (int i = 0; i < p; ++i) {
            int localRes = mainResult[0 + i * p];

            if (localRes == 0) {
                res = 0;
                break;
            }

            if (i == 0) {
                res = localRes;
                if (localRes == 1) {
                    members.push_back(i);
                }
            } else if (localRes == 1) {
                if (members.size() != 0 && members.back() != i + 1) {
                    res = 0;
                    break;
                }
                members.push_back(i);
                if (res == 2) {
                    res = localRes;
                }
            }
        }

//check the validation of the rectangle
        if (res == 1) {
            int xSize = 0;
            int beginY = -1;
            int endY = -1;
            int beginX = -1;
            int endX = -1;
            for (auto it = members.begin(); it != members.end(); ++it) {
                int startX = mainResult[1 + *it * p];
                int startY = mainResult[2 + *it * p];
                int stopX = mainResult[3 + *it * p];
                int stopY = mainResult[4 + *it * p];

                if (it == members.begin()) {
                    beginY = startY;
                    endY = stopY;
                    xSize = stopX - startX;
                    endX = stopX;
                } else {
                    if (xSize != stopX - startX || beginY != startY || endY != stopY || endX != startX - 1) {
                        res = 0;
                        break;
                    }
                    endX = stopX;
                }
            }
        }
        detector.printResult(res);
        if (res == 1) {
            validator.setStart(make_pair(mainResult[1 + members.front() * p], mainResult[2 + members.front() * p]));
            validator.setStop(make_pair(mainResult[3 + members.back() * p], mainResult[4 + members.back() * p]));
            cout << validator << endl << endl;
        }
    }

    delete localMatrix;
    delete localResult;
    delete mainResult;
    MPI_Finalize();

    return EXIT_SUCCESS;
}
