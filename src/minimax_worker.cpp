#include "Minimax.hpp"
#include "TicTacToe.hpp"

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

namespace mpi = boost::mpi;

int main(int argc, char** argv)
{
    // ToDo: potential bug, idk what happens with multiple env objects in same process
    mpi::environment env;

    Minimax minimax;

    // Receive move from spawning process 0
    MPI_Comm parentCommInt;
    MPI_Comm_get_parent(&parentCommInt);
    mpi::communicator parentComm = mpi::communicator(parentCommInt, mpi::comm_create_kind::comm_take_ownership);

    TicTacToeState state;
    parentComm.recv(0, MPITag::State, state);
    std::vector<TicTacToeMove> initMoves;
    parentComm.recv(0, MPITag::Moves, initMoves);
    PlayerId playerId;
    parentComm.recv(0, MPITag::PlayerId, playerId);
    int depth;
    parentComm.recv(0, MPITag::Depth, depth);
   
    std::shared_ptr<TicTacToe> tictactoe = std::make_shared<TicTacToe>(true, false);

    int bestScore;
    std::shared_ptr<Move> bestMove = minimax.getBestMove(tictactoe.get(), state, initMoves[0], playerId, bestScore);

    int score;
    for (int i = 1; i < initMoves.size(); ++i)
    {
        std::shared_ptr<Move> currMove = minimax.getBestMove(tictactoe, state, initMoves[i], playerId, score);
        if (score > bestScore)
        {
            bestMove = currMove;
            bestScore = score;
        }   
    }

    TicTacToeMove tttBestMove = *(dynamic_cast<TicTacToeMove*>(bestMove.get()));

    parentComm.send(0, MPITag::BestMove, tttBestMove);
}