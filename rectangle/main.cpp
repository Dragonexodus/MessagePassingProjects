#include <mpi.h>

#include <fstream>
#include <vector>
#include <sstream>
#include "MatrixBuilder.h"

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
    std::string line;

    //TODO file öffnen, wenn man MPI nutzt!
    // Ohne MPI "../config" um File zu finden!
    std::ifstream configFile("../config");

    if (configFile.is_open()) {
        std::vector<std::string> lines;
        std::getline(configFile,line);
        std::istringstream stringStream(line);
        int mode = 0;
        stringStream >> mode;
        //int parsing
        std::cout << mode << std::endl;
        while (getline(configFile, line)) {
            lines.push_back(line);
        }
        //Beispielausgabe
        for(auto it = lines.begin(); it != lines.end(); ++it){
            std::cout << *it << std::endl;
        }
        configFile.close();
        if (mode == 1 || mode == 2 || mode == 3) {
            MatrixBuilder *matrixBuilder = new MatrixBuilder(mode);
            // TODO: how to realize the matrix?
            // bool matrix[][] = builder->constructMatrix(lines);
             delete matrixBuilder; //später an anderer Stelle nicht vergessen..
        }
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
}