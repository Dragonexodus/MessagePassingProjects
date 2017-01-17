
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

const pair<int, int> RectangleValidator::getYs() {
    return make_pair(getStartY(), getStopY());
}

const pair<int, int> RectangleValidator::getXs() {
    return make_pair(getStartX(), getStopX());
}

//constraints

const bool RectangleValidator::hasValue() {
    return !stopEmpty() && !startEmpty();
}

const bool RectangleValidator::foundNoBlackInLineButRectExists(const int y) {
    return !startEmpty() && stop.second != y;
}

const bool RectangleValidator::inStartLine(const int y) {
    return start.second == y;
}

/**
 * weiß unter schwarz, und rechter rand falls in der vorherigen zeile etwas gefunden <\br>
 * 0 0 <\br>
 * 1 0
 */
const bool RectangleValidator::leftBorderMismatch(const int x, const int y) {
    return getStopY() != y && getStartX() != x;
}

/**
 * linker und rechter rand falls in der vorherigen zeile etwas gefunden
 */
const bool RectangleValidator::xNotUnderUpperBorder(const int x) {
    return x < getStartX() || calcEndX() < x;
}

/**
 * Anfangszeile: 0 ok, 1 ok da erlaubt, 0 Prüfung über Indizeberechnung
 */
const bool RectangleValidator::xIsNotSuccessor(const int x) {
    return (calcEndX() + 1) != x;
}

/**
 * weiß unter schwarz, und rechter Rand falls in der vorherigen Zeile etwas gefunden <\br>
    0 0 <\br>
    0 1
 */
const bool RectangleValidator::rightBorderMismatch(const int x, const int y) {
    return (getStartY() != y && getStopY() == y) && (getStartX() <= x && x <= calcEndX());
}
