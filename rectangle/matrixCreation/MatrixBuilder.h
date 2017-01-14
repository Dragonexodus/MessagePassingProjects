#ifndef PROJECT_MATRIXBUILDER_H
#define PROJECT_MATRIXBUILDER_H

#include <string>
#include <vector>

#define MODE_COMPLETE_RECTANGLE 1
#define MODE_POSITION_PLACEMENT 2
#define MODE_CUSTOM 3

using namespace std;

class MatrixBuilder {
public:
    MatrixBuilder(const int mode, const vector<string> lines);

    ~MatrixBuilder();

    const vector<vector<int>> getMatrix();

private:
    void constructMatrix(const int mode, const vector<string> lines);

    void fillBackground(const int n, const int background);

    void drawCompleteRectangle(const int foreground, const vector<pair<int, int>> &coords);

    vector<vector<int>> matrix;
};


#endif //PROJECT_MATRIXBUILDER_H
