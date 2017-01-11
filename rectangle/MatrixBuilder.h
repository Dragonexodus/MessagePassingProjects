//
// Created by matthias on 11.01.17.
//

#ifndef PROJECT_MATRIXBUILDER_H
#define PROJECT_MATRIXBUILDER_H


#include <fstream>
#include <string>
#include <vector>


class MatrixBuilder {
public:
    MatrixBuilder(const int mode);
    ~MatrixBuilder();

    const int getMode();

    void setMode(const int mode);

    const bool constructMatrix(std::vector<std::string> lines);

private:
    int mode;

};


#endif //PROJECT_MATRIXBUILDER_H
