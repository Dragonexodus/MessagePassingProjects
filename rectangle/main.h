#ifndef PROJECT_MAIN_H
#define PROJECT_MAIN_H

#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>

#define RETURN_COUNT  5
#define INVALID_VALUE -1
#define MASTER 0
#define RUNNING_SEQUENTIELL 1

using namespace std;

void printFromMaster(int rank, string message, ostream &outputStream);

void printFromMaster(int rank, double message, ostream &outputStream);

void parallelSearch(int p, int rank, RectangleDetector &detector, const short *matrix, int n);

void summarize(int p, int rank, RectangleDetector &detector, RectangleValidator &validator, const int *mainResult);

int summarizeRes(int p, const RectangleDetector &detector, const int *mainResult, vector<int> &members);

int checkPositions(const RectangleDetector &detector, const int *mainResult, vector<int> &members, int res);

#endif //PROJECT_MAIN_H
