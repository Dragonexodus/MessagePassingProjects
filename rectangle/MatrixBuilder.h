//
// Created by matthias on 11.01.17.
//

#ifndef PROJECT_MATRIXBUILDER_H
#define PROJECT_MATRIXBUILDER_H


#include <string>
#include <vector>

using namespace std;
class MatrixBuilder {
public:
    MatrixBuilder(const int mode);
    ~MatrixBuilder();

    const int getMode();

    const vector<vector<short>> constructMatrix(vector<string> lines);

private:
    int mode;

    vector<vector<short>> fill(int n, short background);
};


#endif //PROJECT_MATRIXBUILDER_H
