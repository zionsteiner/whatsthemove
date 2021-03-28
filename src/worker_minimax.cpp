#include "Minimax.hpp"

#include <boost/mpi.hpp>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    MPI_Finalize();
}