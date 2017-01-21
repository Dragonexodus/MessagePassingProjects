#ifndef PROJECT_MATRIXBUILDER_H
#define PROJECT_MATRIXBUILDER_H

#include <string>
#include <vector>

enum MODE {
    MODE_COMPLETE_RECTANGLE,
    MODE_POSITION_PLACEMENT,
    MODE_CUSTOM
};

using namespace std;

class MatrixBuilder {

public:
    MatrixBuilder(const int mode, const vector<string> lines);

    ~MatrixBuilder();

    int getN() const;

    short *constructMatrix();

private:

    void fillBackground(const int n, const int background);

    void drawCompleteRectangle(const int foreground, const vector<pair<int, int>> &coords);

    int mode;

    int n;

    vector<string> lines;

    short *matrix;

    void matrixError(string message);
};


#endif //PROJECT_MATRIXBUILDER_H
