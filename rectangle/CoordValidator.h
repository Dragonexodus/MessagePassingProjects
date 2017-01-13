//
// Created by matthias on 13.01.17.
//

#ifndef PROJECT_COORDVALIDATOR_H
#define PROJECT_COORDVALIDATOR_H

#include <vector>

using namespace std;

class CoordValidator {
public:
    CoordValidator(vector<pair<int, int>> coords);

    ~CoordValidator();

    bool validateCoords(int n);

    bool validateRectCoords(int n);

    vector<pair<int, int>> getCoords();

private:
    vector<pair<int, int>> coords;
};


#endif //PROJECT_COORDVALIDATOR_H
