#include "RectangleDetector.h"

int RectangleDetector::testConfigs(const char *term) {
    const vector<vector<int>> &matrix = readFile(term);

    printMatrix(matrix);

    pair<int, RectangleValidator> searchResult = search(matrix);
    if (searchResult.first == MISMATCH_FOUND) {
        cout << "Found some black fields, but no black rectangle!" << endl << endl;;
    } else if (searchResult.first == NO_RECT) {
        cout << "No black fields found!" << endl << endl;
    } else {
        cout << "rectangle found: " << searchResult.second << endl << endl;
    }
    return searchResult.first;
}

//TODO Refactor, weniger returns, aufteilen in diverse methoden, evtl. sogar als objekt
//TODO Aufteilung im Validator
pair<int, RectangleValidator> RectangleDetector::search(const vector<vector<int>> &matrix) {
    bool closedRect = false;
    RectangleValidator validator = RectangleValidator();

    for (int y = 0; y < matrix.size(); y++) {
        for (int x = 0; x < matrix.size(); x++) {
            int color = matrix[y][x];
            if (!color && closedRect) {
                return make_pair(MISMATCH_FOUND, validator);//black found but rectangle is closed;
            }

            if (!color) {
                if (!validator.startEmpty()) {
                    if (validator.getStartY() == y) {
                        if ((validator.calcEndX() + 1) != x) {
                            return make_pair(MISMATCH_FOUND,
                                             validator);//Anfangszeile: 0 ok, 1 ok da erlaubt, 0 Prüfung über Indizeberechnung
                        }
                        validator.incXSize();
                    } else {
                        if (x < validator.getStartX() || validator.calcEndX() < x) {
                            return make_pair(MISMATCH_FOUND,
                                             validator); // linker und rechter rand falls in der vorherigen zeile etwas gefunden
                        }
                        if (validator.getStopY() != y && validator.getStartX() != x) {
                            if (validator.getStartX() <= x && x <= validator.calcEndX()) {
                                return make_pair(MISMATCH_FOUND,
                                                 validator); // weiß unter schwarz, und rechter rand falls in der vorherigen zeile etwas gefunden
                                // 0 0
                                // 1 0
                            }
                        }
                    }
                } else {
                    validator.setStart(make_pair(x, y));
                    validator.incXSize();
                }
                validator.setStop(make_pair(x, y));
            } else {
                if (!validator.startEmpty()) {
                    if (validator.getStopY() != y) {
                        if (x == matrix.size() - 1) {
                            closedRect = true;
                        }
                    }
                }

                if (validator.getStartY() != y && validator.getStopY() == y) {
                    if (validator.getStartX() <= x && x <= validator.calcEndX()) {
                        return make_pair(MISMATCH_FOUND,
                                         validator); // weiß unter schwarz, und rechter rand falls in der vorherigen zeile etwas gefunden
                        // 0 0
                        // 0 1
                    }
                }
            }
        }
    }
    if (!validator.stopEmpty() && !validator.startEmpty()) {
        return make_pair(RECT_FOUND, validator);
    }
    return make_pair(NO_RECT, validator);//no rect found
}

/**
 *
 * @return a matrix with found values, if nothing found an empty matrix is returned
 */
const vector<vector<int>> RectangleDetector::readFile(const char *term) {

    ifstream configFile(term);

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
        const vector<vector<int>> matrix = matrixBuilder.constructMatrix();
        return matrix;
    } else {
        cout << "Unable to open file" << endl;
        const vector<vector<int>> matrix;
        return matrix;
    }
}

void RectangleDetector::printMatrix(vector<vector<int>> matrix) {
    for (auto it = matrix.begin(); it != matrix.end(); ++it) {
        for (auto elem = it->begin(); elem != it->end(); ++elem) {
            cout << *elem << " ";
        }
        cout << endl;
    }
}

RectangleDetector::RectangleDetector() {}

RectangleDetector::~RectangleDetector() {}
