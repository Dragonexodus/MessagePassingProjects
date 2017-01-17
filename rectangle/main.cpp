#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>

int **initEmpty();

using namespace std;

void copy(int **newarray, vector<vector<int>> matrix, int n);

int **initEmpty();
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
    MPI_Status status;

    RectangleDetector detector = RectangleDetector();
    vector<vector<int>> *matrix = new vector<vector<int>>;
    vector<vector<int>> *localMatrix = new vector<vector<int>>;
    //double startTimer = MPI_Wtime();
    unsigned long localN = 0;
    int localMatrixSize = 0;

    if (rank == MASTER) {
        *matrix = detector.readFile("config");
        localN = matrix->size() / p;
        int localMatrixSize = (int) (matrix->front().size() * localN);
        MPI_Bcast(&localMatrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        detector.printMatrix(*matrix);
        cout << "size of matrix:" << matrix->size() << endl;
        int **newMatrix = initEmpty();
        copy(newMatrix, *matrix, matrix->size());
        detector.printOldMatrix(newMatrix, 8, 8);
        for (int i = 1; i < localN; i++) {
            //TODO convert to array
            MPI_Send(&(newMatrix[i * localN][0]), localMatrixSize, MPI_INT, i, i, MPI_COMM_WORLD);
        }
    } else {
        MPI_Bcast(&localMatrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        int **array = initEmpty();
        MPI_Recv(array, localMatrixSize, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        if (rank == 1) {
            detector.printOldMatrix(array, 2, 8);
        }
        for (int i = 0; i < 8; ++i) {
            delete array[i];
        }
        delete array;
    }



    /*if(rank == MASTER){

        pair<int, RectangleValidator> searchResult = detector.search(*matrix);
        if (searchResult.first == detector.MISMATCH_FOUND) {
            cout << "Found some black fields, but no black rectangle!" << endl << endl;;
        } else if (searchResult.first == detector.NO_RECT) {
            cout << "No black fields found!" << endl << endl;
        } else {
            cout << "rectangle found: " << searchResult.second << endl << endl;
        }
        double stopTimer = MPI_Wtime();
        std::cout << "Benötigte Zeit: " << stopTimer - startTimer << std::endl;
    }*/
    if (matrix != NULL) {
        delete matrix;
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

int **initEmpty() {
    int **array = new int *[8];
    for (int i = 0; i < 8; ++i) {
        array[i] = new int[8];
    }
    return array;
}

void copy(int **newarray, vector<vector<int>> matrix, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            newarray[i][j] = matrix[i][j];
        }
    }
}
