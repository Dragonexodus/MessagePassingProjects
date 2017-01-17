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
                    if (validator.inStartLine(y)) {
                        if (validator.xIsNotSuccessor(x)) {
                            return make_pair(MISMATCH_FOUND, validator);
                        }
                        validator.incXSize();
                    } else {
                        if (validator.xNotUnderUpperBorder(x)) {
                            return make_pair(MISMATCH_FOUND, validator);
                        }
                        if (validator.leftBorderMismatch(x, y)) {
                            return make_pair(MISMATCH_FOUND, validator);
                        }
                    }
                } else {
                    validator.setStart(make_pair(x, y));
                    validator.incXSize();
                }
                validator.setStop(make_pair(x, y));
            } else {
                if (validator.foundNoBlackInLineButRectExists(y)) {
                    if (x == matrix.size() - 1) {
                        closedRect = true;
                    }
                }
                if (validator.rightBorderMismatch(x, y)) {
                    return make_pair(MISMATCH_FOUND, validator);
                }
            }
        }
    }
    if (validator.hasValue()) {
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
