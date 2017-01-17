#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>

int *initEmpty(int sizeX, int sizeY);

using namespace std;

void _copy(int **newarray, vector<vector<int>> matrix, int sizeX, int sizeY);

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
    //double startTimer = MPI_Wtime();
    int localN = 0;
    int localMatrixSize = 0;
    vector<vector<int>> *matrix = new vector<vector<int>>;
    if (rank == MASTER) {
        *matrix = detector.readFile("config");
        localN = matrix->size() / p;
        int localMatrixSize = matrix->front().size() * localN;

        MPI_Bcast(&localMatrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

        detector.printMatrix(*matrix);
        cout << "size of matrix:" << matrix->size() << endl;
        int *newMatrix = initEmpty(matrix->size(), matrix->size());
        _copy(newMatrix, *matrix, matrix->size(), matrix->size());

        for (int i = 1; i < p; i++) {
            //TODO convert to array
            int pos = i * localN;
            //   cout<<"sending array with size:"<<localMatrixSize<<" from pos: "<<pos<<":"<<0<<endl;
            MPI_Send(&newMatrix[pos], localMatrixSize, MPI_INT, i, 100, MPI_COMM_WORLD);
        }
    } else {
        MPI_Bcast(&localMatrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
        int *array = initEmpty(2, 8);

        MPI_Recv(&array[0], localMatrixSize, MPI_INT, 0, 100, MPI_COMM_WORLD, &status);
        cout << "r" << rank << endl;

        if (rank == 3) {
            // detector.printOldMatrix(array, 2, 8);
        }
        for (int i = 0; i < 2; ++i) {
            delete array[i];
        }
        delete array;
    }
    /*MPI_Scatter(rectangle, rowsPart * columns, MPI_CHAR, rectanglePart,
                rowsPart * columns, MPI_CHAR, 0, MPI_COMM_WORLD);
*/


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

    //TODO Segmenentation-Fault wegen nicht korrekt freigegebenen speicher

    MPI_Finalize();

    return EXIT_SUCCESS;
}

int *initEmpty(int sizeX, int sizeY) {
    int *array = new int[sizeY * sizeX];
    for (int i = 0; i < sizeY * sizeX; ++i) {
        array[i] = 0;
    }
    return array;
}

void _copy(int *newarray, vector<vector<int>> matrix, int sizeX, int sizeY) {
    for (int i = 0; i < sizeY; ++i) {
        for (int j = 0; j < sizeX; ++j) {
            newarray[i * sizeX + j] = matrix[i][j];
        }
    }
}
