#ifndef PROJECT_COORDVALIDATOR_H
#define PROJECT_COORDVALIDATOR_H

#include <vector>

#define IS_NOT_VALID false
#define IS_VALID true
#define THREE_POINTS_TO_RECTANGLE 3

using namespace std;

class CoordValidator {
public:
    CoordValidator(const vector<pair<int, int>> coords, const int n, const int mode);

    ~CoordValidator();

    const bool getValidation();

private:
    bool validateCoordDimensions();

    bool validateRectCoords();

    vector<pair<int, int>> coords;
    int n;
    bool isValid;
};


#endif //PROJECT_COORDVALIDATOR_H
