
#include "RectangleValidator.h"

RectangleValidator::RectangleValidator() {
    start = make_pair(-1, -1);
    stop = make_pair(-1, -1);
    xSize = 0;
}

RectangleValidator::~RectangleValidator() {}

const int RectangleValidator::getStartX() {
    return start.first;
}

const int RectangleValidator::getStopX() {
    return stop.first;
}

const int RectangleValidator::getStartY() {
    return start.second;
}

const int RectangleValidator::getStopY() {
    return stop.second;
}


const pair<int, int> &RectangleValidator::getStart() const {
    return start;
}

void RectangleValidator::setStart(const pair<int, int> &start) {
    RectangleValidator::start = start;
}

const pair<int, int> &RectangleValidator::getStop() const {
    return stop;
}

void RectangleValidator::setStop(const pair<int, int> &stop) {
    RectangleValidator::stop = stop;
}

bool RectangleValidator::startEmpty() {
    return start.first == -1 || start.second == -1;
}

bool RectangleValidator::stopEmpty() {
    return stop.first == -1 || stop.second == -1;
}

std::ostream &operator<<(std::ostream &os, const RectangleValidator &validator) {
    os << "start: " << validator.start.first << ":" << validator.start.second << " stop: " << validator.stop.first
       << ":" << validator.stop.second;
    return os;
}

void RectangleValidator::incXSize() {
    xSize++;
}

int RectangleValidator::getXSize() const {
    return xSize;
}

int RectangleValidator::calcEndX() const {
    return start.first + xSize - 1;
}
