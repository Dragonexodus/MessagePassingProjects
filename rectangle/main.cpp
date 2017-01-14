#include <mpi.h>
#include <fstream>
#include <vector>
#include <sstream>
#include "MatrixBuilder.h"

using namespace std;

const vector<vector<short>> readFile();

void printMatrix(vector<vector<short>> matrix);

int search(const vector<vector<short>> &matrix);

bool indexRectHasValues(vector<vector<int>> indexRect);

int main(int argc, char **argv) {
    const int MASTER = 0;
    int p;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (rank == MASTER) {
        double startTimer = MPI_Wtime();
        const vector<vector<short>> &matrix = readFile();
        printMatrix(matrix);

        int searchResult = search(matrix);
        if (searchResult == 0) {
            cout << "Found some black fields, but no black rectangle!" << std::endl;
        } else if (searchResult == 2) {
            cout << "No black fields found!" << std::endl;
        }

        double stopTimer = MPI_Wtime();
        std::cout << "Benötigte Zeit: " << stopTimer - startTimer << std::endl;
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

int search(const vector<vector<short>> &matrix) {
    vector<vector<int>> indexRect;
    vector<int> indexLine;
    bool closedRect = false;
    int yBeginOfRect = -1;

    for (int y = 0; y < matrix.size(); ++y) {
        if (y > 0 && indexLine.size() > 0) {
            indexRect.push_back(indexLine);
            indexLine.clear();
        }
        bool foundInLine = false;
        int indexUntilFound = 0;
        for (int x = 0; x < matrix.size(); ++x) {
            short color = matrix[x][y];
            if (color == 0 && closedRect) {
                return 0;//black found but rectangle is closed;
            }
            if (color == 0) {
                if (indexRectHasValues(indexRect)) {
                    vector<int> &lastLine = indexRect[indexRect.size() - 1];
                    if (lastLine[lastLine.size() - 1] < x || lastLine[0] > x) {
                        return 0;//black found, but not under upper black line
                    }
                    if (!foundInLine && lastLine[0] != x) {
                        return 0;//black found, but upper line begins somewhere else
                    }
                } else { yBeginOfRect = y; }

                foundInLine = true;
                indexLine.push_back(x);
                indexUntilFound++;
            } else {
                if (indexRectHasValues(indexRect)) {
                    if (foundInLine) {
                        if (indexRect[indexRect.size() - 1][indexUntilFound] == x) {
                            return 0;//white in line of black but with upper black line
                        }
                    } else {
                        if (x == matrix.size() - 1) {
                            closedRect = true;
                        }
                    }

                }
            }
        }
    }
    if (indexRectHasValues(indexRect)) {
        vector<int> &firstLine = indexRect[0];
        vector<int> &lastLine = indexRect[indexRect.size() - 1];
        cout << "rectangle found: " << firstLine[0] << ":" << yBeginOfRect << " "
             << firstLine[firstLine.size() - 1] << ":" << yBeginOfRect << " "
             << lastLine[0] << ":" << firstLine[0] + indexRect.size() - 1 << " "
             << lastLine[lastLine.size() - 1] << ":" << firstLine[0] + indexRect.size() - 1 << endl;
        return 1;
    }
    return 2;//no rect found
}


const vector<vector<short>> readFile() {
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
        //print all lines from file
        for (auto it = lines.begin(); it != lines.end(); ++it) {
            cout << *it << endl;
        }
        cout << endl;

        configFile.close();
        //create the matrix
        if (mode > 0 && mode < 4) {
            MatrixBuilder *matrixBuilder = new MatrixBuilder(mode);
            const vector<vector<short>> &matrix = matrixBuilder->constructMatrix(lines);
            delete matrixBuilder;
            return matrix;
        }
    } else {
        cout << "Unable to open file" << endl;
    }
    throw -1;
}

bool indexRectHasValues(vector<vector<int>> indexRect) {
    return indexRect.size() > 0 && indexRect[indexRect.size() - 1].size() > 0;
}

void printMatrix(vector<vector<short>> matrix) {
    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        for (auto elem = it->begin(); elem != it->end(); ++elem) {
            cout << *elem << " ";
        }
        cout << endl;
    }
}
