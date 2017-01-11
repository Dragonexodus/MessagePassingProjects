#include <mpi.h>

#include <fstream>
#include <vector>
#include "MatrixBuilder.h"

using namespace std;

void readFile();

int main(int argc, char **argv) {
    const int MASTER = 0;
    MPI::Init();
    MPI::Intracomm &world = MPI::COMM_WORLD;

    if (world.Get_rank() == MASTER) {
        readFile();
        //Testausgabe
        /*for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << rectangleTrue[i * 4 + j];
            }
            std::cout << std::endl;
        }*/
    }

    auto startTimer = MPI::Wtime();
    auto stopTimer = MPI::Wtime();

    MPI::Finalize();

    return EXIT_SUCCESS;
}

void readFile() {
    string line;
    ifstream myfile("config");
    if (myfile.is_open()) {
        int mode = atoi(getline(myfile, line));
        vector<string> lines;
        while (getline(myfile, line)) {
            lines.push_back(line);
        }
        myfile.close();
        if (mode == 1 || mode == 2 || mode == 3) {
            MatrixBuilder *builder = new MatrixBuilder(mode);
            // TODO: how to realize the matrix?
            // bool matrix[][] = builder->constructMatrix(lines);
        }
    } else {
        cout << "Unable to open file";
    }
}