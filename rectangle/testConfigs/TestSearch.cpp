#include "../RectangleDetector.h"
#include <assert.h>

int main(int argc, char **argv) {

    RectangleDetector detector = RectangleDetector();
    assert(detector.testConfigs("nothingFound1") == detector.NO_RECT);
    assert(detector.testConfigs("rectFound1") == detector.RECT_FOUND);
    assert(detector.testConfigs("rectFound2") == detector.RECT_FOUND);
    assert(detector.testConfigs("rectFound3") == detector.RECT_FOUND);
    assert(detector.testConfigs("rectFound4") == detector.RECT_FOUND);
    assert(detector.testConfigs("rectFound5") == detector.RECT_FOUND); // TODO Mode 0 wrong indicies
    assert(detector.testConfigs("rectFound6") == detector.RECT_FOUND);
    assert(detector.testConfigs("somethingElseFound1") == detector.MISMATCH_FOUND);
    assert(detector.testConfigs("somethingElseFound2") == detector.MISMATCH_FOUND);
    assert(detector.testConfigs("somethingElseFound3") == detector.MISMATCH_FOUND);
    assert(detector.testConfigs("somethingElseFound4") == detector.MISMATCH_FOUND);
    assert(detector.testConfigs("somethingElseFound5") == detector.MISMATCH_FOUND);
    return EXIT_SUCCESS;
}