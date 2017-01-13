#include <mpi.h>

#include <fstream>
#include <vector>
#include <sstream>
#include "MatrixBuilder.h"

using namespace std;

void readFile();

int main(int argc, char **argv) {
    const int MASTER = 0;
    int p;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (rank == MASTER) {
        double startTimer = MPI_Wtime();
        readFile();
        double stopTimer = MPI_Wtime();
        std::cout << "Benötigte Zeit: " << stopTimer - startTimer;
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

void readFile() {
    string line;

    ifstream configFile("config");

    if (configFile.is_open()) {
        vector<string> lines;
        getline(configFile, line);
        istringstream stringStream(line);
        int mode = 0;
        stringStream >> mode;
        //int parsing
        cout << mode << endl;
        while (getline(configFile, line)) {
            lines.push_back(line);
        }
        //print all lines
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            cout << *it << endl;
        }
        cout << endl;

        configFile.close();
        //create and print the matrix
        if (mode == 1 || mode == 2 || mode == 3) {
            MatrixBuilder *matrixBuilder = new MatrixBuilder(mode);
            const vector<vector<short>> &matrix = matrixBuilder->constructMatrix(lines);
            matrixBuilder->printMatrix(matrix);
            delete matrixBuilder;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
}