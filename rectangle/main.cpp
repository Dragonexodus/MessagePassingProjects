#include <mpi.h>

#include <fstream>
#include <vector>
#include <sstream>
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
                cout << rectangleTrue[i * 4 + j];
            }
            cout << endl;
        }*/
    }

    auto startTimer = MPI::Wtime();
    auto stopTimer = MPI::Wtime();

    MPI::Finalize();

    return EXIT_SUCCESS;
}

void readFile() {
    string line;

    //TODO file öffnen, wenn man MPI nutzt!
    // Ohne MPI "../config" um File zu finden!
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
        //Beispielausgabe
        for(auto it = lines.begin(); it != lines.end(); ++it){
            cout << *it << endl;
        }
        configFile.close();
        if (mode == 1 || mode == 2 || mode == 3) {
            MatrixBuilder *matrixBuilder = new MatrixBuilder(mode);
            const vector<vector<short>> &matrix = matrixBuilder->constructMatrix(lines);
            for (auto it = matrix.begin(); it != matrix.end(); ++it) {
                for (auto elem = it->begin(); elem != it->end(); ++elem) {
                    cout << *elem << " ";
                }
                cout << endl;
            }
            // TODO: how to realize the matrix?
            // bool matrix[][] = builder->constructMatrix(lines);
             delete matrixBuilder; //später an anderer Stelle nicht vergessen..
        }
    } else {
        cout << "Unable to open file" << endl;
    }
}