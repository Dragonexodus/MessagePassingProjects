#include "CoordValidator.h"

CoordValidator::CoordValidator(const vector<pair<int, int>> coords, const int n, const int mode) {
    this->coords = coords;
    this->n = n;

    isValid = IS_NOT_VALID;

    if (mode == 1) {
        isValid = validateRectCoords();
    } else {
        isValid = validateCoordDimensions();
    }
}

bool CoordValidator::validateCoordDimensions() {
    bool valid = IS_NOT_VALID;
    if (!coords.empty()) {
        valid = IS_VALID;
        for (auto it = coords.begin(); it != coords.end(); ++it) {
            valid = valid && it->first < n && it->first >= 0
                    && it->second < n && it->second >= 0;
        }
    }
    return valid;
}

bool CoordValidator::validateRectCoords() {
    bool valid = IS_NOT_VALID;
    if (coords.size() == THREE_POINTS_TO_RECTANGLE && n > 0) {
        int a1 = coords[1].first - coords[0].first;
        int b1 = coords[2].second - coords[0].second;

        bool edgeA1Straight = coords[1].second == coords[0].second;
        bool edgeB1Straight = coords[2].first == coords[0].first;
        bool notNegativeAndLowerThanN = validateCoordDimensions();
        valid = a1 > 0 && b1 > 0 && edgeA1Straight && edgeB1Straight && notNegativeAndLowerThanN;
    }
    return valid;
}

CoordValidator::~CoordValidator() {
}

const bool CoordValidator::getValidation() {
    return isValid;
}