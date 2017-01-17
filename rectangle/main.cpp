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
    //TODO verschiebe indicies
    int *localResult = new int[5];
    localResult[0] = detectorResult.first;
    localResult[1] = validator.getStartX();
    localResult[2] = validator.getStopX();
    localResult[3] = validator.getStartY();
    localResult[4] = validator.getStopX();
    int *mainResult = new int[5 * p];
    MPI_Gather(localResult, 5, MPI_INT, mainResult, 5, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == MASTER) {
        //TODO: werte alle Results aus
        detector.printOldMatrix(mainResult, p, 5);
    }

    delete localMatrix;
    delete localResult;
    delete mainResult;
    MPI_Finalize();

    return EXIT_SUCCESS;
}
