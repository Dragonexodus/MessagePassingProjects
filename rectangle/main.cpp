#include <mpi.h>

#include "testRectangles.h"

int main(int argc, char **argv) {
    const int MASTER = 0;

    MPI::Init();
    MPI::COMM_WORLD.Get_size();
    MPI::COMM_WORLD.Get_rank();

    if (MPI::COMM_WORLD.Get_rank() == MASTER) {
        //Testausgabe
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << rectangleTrue[i * 4 + j];
            }
            std::cout << std::endl;
        }
    }

    auto startTimer = MPI::Wtime();
    auto stopTimer = MPI::Wtime();

    MPI::Finalize();

    return EXIT_SUCCESS;
}
