#include "RectangleDetector.h"

int RectangleDetector::testConfigs(const char *term) {
    const pair<short *, int> result = readFile(term);
    short *matrix = result.first;
    int n = result.second;
    printOldMatrix(matrix, n, n);

    pair<int, RectangleValidator> searchResult = search(matrix, n, n);
    printResult(searchResult.first);
    if (searchResult.first == RECT_FOUND) {
        //cout << searchResult.second << endl;
    }
    return searchResult.first;
}

void RectangleDetector::printResult(int res) {
    if (res == MISMATCH_FOUND) {
        //cout << "Found some black fields, but no black rectangle!" << endl << endl;;
    } else if (res == NO_RECT) {
        //cout << "No black fields found!" << endl << endl;
    } else {
        //cout << "rectangle found: " << endl;
    }
}

pair<int, RectangleValidator> RectangleDetector::search(short *matrix, int n, int localSize) {

    bool closedRect = false;
    RectangleValidator validator = RectangleValidator();

    for (int y = 0; y < localSize; y++) {
        for (int x = 0; x < n; x++) {
            short color = matrix[y * n + x];
            if (!color && closedRect) {
                //cout << "closedRect" << endl;
                return make_pair(MISMATCH_FOUND, validator);//black found but rectangle is closed;
            }

            if (!color) {
                if (!validator.startEmpty()) {
                    if (validator.inStartLine(y)) {
                        if (validator.xIsNotSuccessor(x)) {
                            //cout << "xIsNotSuccessor" << endl;
                            return make_pair(MISMATCH_FOUND, validator);
                        }
                        validator.incXSize();
                    } else {
                        if (validator.xNotUnderUpperBorder(x)) {
                            //cout << "xNotUnderUpperBorder" << endl;
                            return make_pair(MISMATCH_FOUND, validator);
                        }
                        if (validator.leftBorderMismatch(x, y)) {
                            //cout << "leftBorderMismatch" << endl;
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
                    if (x == n - 1) {
                        closedRect = true;
                    }
                }
                if (validator.rightBorderMismatch(x, y)) {
                    //cout << "rightBorderMismatch" << endl;
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
const pair<short *, int> RectangleDetector::readFile(const char *term) {

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
        short *matrix = matrixBuilder.constructMatrix();
        int n = matrixBuilder.getN();
        return make_pair(matrix, n);
    } else {
        //cout << "Unable to open file" << endl;
        throw "";
    }
}

void RectangleDetector::printOldMatrix(short *array, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            //cout << array[i * m + j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;
}

void RectangleDetector::printOldMatrix(int *array, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            //cout << array[i * m + j] << " ";
        }
        //cout << endl;
    }
    //cout << endl;
}

RectangleDetector::RectangleDetector() {}

RectangleDetector::~RectangleDetector() {}
