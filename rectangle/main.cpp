#include <iostream>
#include "RectangleDetector.h"
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {
    const int MASTER = 0;
    int p;
    int rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if (rank == MASTER) {
        double startTimer = MPI_Wtime();
        RectangleDetector detector = RectangleDetector();
        detector.testConfigs("config");
        double stopTimer = MPI_Wtime();
        std::cout << "Benötigte Zeit: " << stopTimer - startTimer << std::endl;
    }

    MPI_Finalize();

    return EXIT_SUCCESS;
}
