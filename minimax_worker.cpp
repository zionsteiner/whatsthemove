#include "Minimax.hpp"

#include <boost/mpi.hpp>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

namespace mpi = boost::mpi;

int main(int argc, char** argv)
{
    mpi::environment env(argc, argv);
    mpi::communicator world;

    Minimax minimax;

    // Receive move from spawning process 0
    MPI_Comm parentComm;
    MPI_Comm_get_parent(&parentComm);
    mpi::communicator parentComm(parentComm, mpi::comm_create_kind::comm_take_ownership);

    Move move;
   
    Move bestMove = minimax.getBestMove(TicTacToe(true, false), 3, 0);

    MPI_Finalize();
}