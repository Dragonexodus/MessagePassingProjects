//
// Created by matthias on 11.01.17.
//

#ifndef PROJECT_MATRIXBUILDER_H
#define PROJECT_MATRIXBUILDER_H


#include <fstream>
#include <string>
#include <vector>

using namespace std;
class MatrixBuilder {
public:
    MatrixBuilder(const int mode);
    ~MatrixBuilder();

    const int getMode();

    const vector<vector<short>> constructMatrix(vector<string> lines);


    void printMatrix(vector<vector<short>> matrix);

private:
    int mode;

    vector<pair<int, int>> splitAndParseToCoords(const string &s, char delim);

    bool validateRectCoords(vector<pair<int, int>> coords, int i);

    vector<vector<short>> fill(int n, short background);

    bool validateCoords(vector<pair<int, int>> coords, int n);

    vector<short> splitAndParseToLine(const string &s, char delim);
};


#endif //PROJECT_MATRIXBUILDER_H
