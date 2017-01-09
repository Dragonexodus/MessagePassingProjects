#ifndef PROJECT_TESTRECTANGLES_H
#define PROJECT_TESTRECTANGLES_H

#define RECTANGLE_SIZE 4*4

const static int rectangleBlack[RECTANGLE_SIZE] = {0,0,0,0,
                                                   0,0,0,0,
                                                   0,0,0,0,
                                                   0,0,0,0};

const static int rectangleWhite[RECTANGLE_SIZE] = {1,1,1,1,
                                                   1,1,1,1,
                                                   1,1,1,1,
                                                   1,1,1,1};

const static int rectangleTrue[RECTANGLE_SIZE] = {0,0,0,0,
                                                  0,1,1,0,
                                                  0,1,1,0,
                                                  0,0,0,0};

const static int rectangleFals[RECTANGLE_SIZE] = {1,1,1,1,
                                                  1,1,0,1,
                                                  1,1,1,1,
                                                  1,1,1,1};

#endif //PROJECT_TESTRECTANGLES_H
