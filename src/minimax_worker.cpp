#include "Minimax.hpp"
#include "TicTacToe.hpp"

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

namespace mpi = boost::mpi;

int main(int argc, char** argv)
{
    mpi::environment env;

    Minimax minimax;

    // Receive move from spawning process 0
    MPI_Comm parentCommInt;
    MPI_Comm_get_parent(&parentCommInt);
    mpi::communicator parentComm = mpi::communicator(parentCommInt, mpi::comm_create_kind::comm_take_ownership);

    TicTacToeState state;
    parentComm.recv(0, MPI_ANY_TAG, state);
    std::vector<TicTacToeMove> initMoves;
    parentComm.recv(0, MPI_ANY_TAG, initMoves);
   
    TicTacToe tictactoe(true, false);

    // Get depth from argv
    int depth = 3;


    std::shared_ptr<Move> bestMove = minimax.getBestMove(tictactoe, state, initMoves[0], depth, 0);
    for (int i = 1; i < initMoves.size(); ++i)
    {
        std::shared_ptr<Move> currMove = minimax.getBestMove(tictactoe, state, initMoves[i], depth, 0);
        std::vector<int> scores = tictactoe.scoreGameState(state);
    }

    TicTacToeMove tttBestMove = *(dynamic_cast<TicTacToeMove*>(bestMove.get()));

    parentComm.send(0, 0, bestMove);

    MPI_Finalize();
}