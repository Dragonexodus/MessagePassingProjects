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

    const int *getMatrix();

    int getMode() const;

    void setMode(int mode);

    int getN() const;

    const vector<string> &getLines() const;

    void setLines(const vector<string> &lines);

    int *constructMatrix();

private:

    void fillBackground(const int n, const int background);

    void drawCompleteRectangle(const int foreground, const vector<pair<int, int>> &coords);

    int mode;

    int n;

    vector<string> lines;

    int *matrix;
};


#endif //PROJECT_MATRIXBUILDER_H
