#include "main.h"

int main(int argc, char **argv) {
    const int MASTER = 0;
    int p;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (rank == MASTER) {
        double startTimer = MPI_Wtime();
        const vector<vector<int>> &matrix = readFile();

        printMatrix(matrix);

        int searchResult = search(matrix);
        if (searchResult == MISMATCH_FOUND) {
            cout << "Found some black fields, but no black rectangle!" << std::endl;
        } else if (searchResult == NO_RECT) {
            cout << "No black fields found!" << std::endl;
        }

        double stopTimer = MPI_Wtime();
        std::cout << "Benötigte Zeit: " << stopTimer - startTimer << std::endl;
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}

//TODO search segmentation fault for mode 3
//TODO Refactor, weniger returns, aufteilen in diverse methoden, evtl. sogar als objekt
int search(const vector<vector<int>> &matrix) {
    vector<vector<int>> indexRect;
    vector<int> indexLine;
    bool closedRect = false;
    int yBeginOfRect = -1;

    //begin of magic o.o??
    for (int y = 0; y < matrix.size(); ++y) {
        if (y > 0 && indexLine.size() > 0) {
            indexRect.push_back(indexLine);
            indexLine.clear();
        }
        bool foundInLine = false;
        int indexUntilFound = 0;
        for (int x = 0; x < matrix.size(); ++x) {
            int color = matrix[x][y];
            if (!color && closedRect) {
                return MISMATCH_FOUND;//black found but rectangle is closed;
            }
            if (!color) {
                if (indexRectHasValues(indexRect)) {
                    vector<int> &lastLine = indexRect[indexRect.size() - 1];
                    if (lastLine[lastLine.size() - 1] < x || lastLine.front() > x) {
                        return MISMATCH_FOUND;//black found, but not under upper black line
                    }
                    if (!foundInLine && lastLine.front() != x) {
                        return MISMATCH_FOUND;//black found, but upper line begins somewhere else
                    }
                } else {
                    yBeginOfRect = y;
                }

                foundInLine = true;
                indexLine.push_back(x);
                indexUntilFound++;
            } else {
                if (indexRectHasValues(indexRect)) {
                    if (foundInLine) {
                        if (indexRect[indexRect.size() - 1][indexUntilFound] == x) {
                            return MISMATCH_FOUND;//white in line of black but with upper black line
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
        vector<int> &firstLine = indexRect.front();
        vector<int> &lastLine = indexRect.back();
        cout << "rectangle found: " << firstLine.front() << ":" << yBeginOfRect << " "
             << firstLine[firstLine.size() - 1] << ":" << yBeginOfRect << " "
             << lastLine.front() << ":" << firstLine.front() + indexRect.size() - 1 << " "
             << lastLine[lastLine.size() - 1] << ":" << firstLine.front() + indexRect.size() - 1 << endl;
        return RECT_FOUND;
    }
    return NO_RECT;//no rect found
}

/**
 *
 * @return a matrix with found values, if nothing found an empty matrix is returned
 */
const vector<vector<int>> readFile() {

    ifstream configFile("config");

    if (configFile.is_open()) {
        string line;
        vector<string> lines;
        getline(configFile, line);
        istringstream stringStream(line);
        int mode = 0;
        stringStream >> mode;

        while (getline(configFile, line)) {
            lines.push_back(line);
        }

        configFile.close();

        MatrixBuilder matrixBuilder = MatrixBuilder(mode, lines);
        const vector<vector<int>> matrix = matrixBuilder.getMatrix();
        return matrix;
    } else {
        cout << "Unable to open file" << endl;
        const vector<vector<int>> matrix;
        return matrix;
    }
}

bool indexRectHasValues(vector<vector<int>> indexRect) {
    return !indexRect.empty() && !indexRect.back().empty();
}

void printMatrix(vector<vector<int>> matrix) {
    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        for (auto elem = it->begin(); elem != it->end(); ++elem) {
            cout << *elem << " ";
        }
        cout << endl;
    }
    cout << endl;
}
