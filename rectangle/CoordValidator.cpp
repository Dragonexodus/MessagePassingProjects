//
// Created by matthias on 13.01.17.
//

#include "CoordValidator.h"

CoordValidator::CoordValidator(vector<pair<int, int>> coords) { this->coords = coords; }

vector<pair<int, int>> CoordValidator::getCoords() {
    return vector<pair<int, int>>();
}

bool CoordValidator::validateCoords(int n) {
    bool valid = false;
    if (coords.size() > 0) {
        valid = true;
        for (int i = 0; i < coords.size(); ++i) {
            valid = valid && coords[i].first < n && coords[i].first >= 0 && coords[i].second < n &&
                    coords[i].second >= 0;
        }
    }
    return valid;
}

bool CoordValidator::validateRectCoords(int n) {
    bool valid = false;
    if (coords.size() == 3) {
        int a1 = coords[1].first - coords[0].first;
        int b1 = coords[2].second - coords[0].second;

        bool edgeA1Straight = coords[1].second == coords[0].second;
        bool edgeB1Straight = coords[2].first == coords[0].first;
        bool lowerThanN = coords[0].first < n && coords[1].first < n && coords[2].first < n &&
                          coords[0].second < n && coords[1].second < n && coords[2].second < n;
        bool notNegative = coords[0].first >= 0 && coords[1].first >= 0 && coords[2].first >= 0 &&
                           coords[0].second >= 0 && coords[1].second >= 0 && coords[2].second >= 0 && n > 0;
        valid = a1 > 0 && b1 > 0 && edgeA1Straight && edgeB1Straight && notNegative && lowerThanN;
    }
    return valid;
}


CoordValidator::~CoordValidator() {
}
