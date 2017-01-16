
#ifndef PROJECT_RECTANGLEVALIDATOR_H
#define PROJECT_RECTANGLEVALIDATOR_H

#include <utility>
#include <ostream>

using namespace std;

class RectangleValidator {

public:

    RectangleValidator();

    ~RectangleValidator();

    const pair<int, int> &getStart() const;

    void setStart(const pair<int, int> &start);

    const pair<int, int> &getStop() const;

    void setStop(const pair<int, int> &start);

    bool startEmpty();

    bool stopEmpty();

    const int getStartX();

    const int getStopX();

    const int getStartY();

    const int getStopY();

    void incXSize();

    int getXSize() const;

    int calcEndX() const;

    friend std::ostream &operator<<(std::ostream &os, const RectangleValidator &validator);

private:
    pair<int, int> start;

    pair<int, int> stop;

    int xSize;
};


#endif //PROJECT_RECTANGLEVALIDATOR_H
