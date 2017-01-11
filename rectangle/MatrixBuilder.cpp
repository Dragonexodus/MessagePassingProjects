#include "MatrixBuilder.h"

MatrixBuilder::MatrixBuilder(int mode) {
    this->mode = mode;
}

MatrixBuilder::~MatrixBuilder() {}

const int MatrixBuilder::getMode() {
    return mode;
}

void MatrixBuilder::setMode(const int mode) {
    this->mode = mode;
}

//??
/*
 * const bool MatrixBuilder::constructMatrix(std::vector<std::string> lines){
    //TODO read lines
    bool matrix[4][4] = {{0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0},
                         {0,0,0,0}};
    return matrix;
}*/
