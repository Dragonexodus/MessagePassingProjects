//
// Created by matthias on 11.01.17.
//

#ifndef PROJECT_MATRIXBUILDER_H
#define PROJECT_MATRIXBUILDER_H


#include <fstream>
#include <string>
#include <bits>
#include <vector>

class constructMatrix;

class MatrixBuilder {
public:
    MatrixBuilder(int mode) {
        this->mode = mode;
    }

    int getMode() const {
        return mode;
    }

    void setMode(int mode) {
        MatrixBuilder::mode = mode;
    }

    //bool constructMatrix(std::vector<std::string> lines)[][];

private:
    int mode;


};


#endif //PROJECT_MATRIXBUILDER_H
