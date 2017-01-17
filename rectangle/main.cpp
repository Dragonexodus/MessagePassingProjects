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
    const pair<int, RectangleValidator> &result = detector.search(localMatrix, n, localN);
    if (result.first == detector.MISMATCH_FOUND) {
        cout << "Found some black fields, but no black rectangle!" << endl << endl;;
    } else if (result.first == detector.NO_RECT) {
        cout << "No black fields found!" << endl << endl;
    } else {
        cout << "rectangle found: " << result.second << endl << endl;
    }
    //TODO Gather 5er Array und verschiebe indicies, dann ermittle Rechteckkoordinaten
    delete localMatrix;
    MPI_Finalize();

    return EXIT_SUCCESS;
}
