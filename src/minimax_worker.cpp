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

    // Receive move from spawning process 0
    MPI_Comm parentCommInt;
    MPI_Comm_get_parent(&parentCommInt);
    mpi::communicator parentComm = mpi::communicator(parentCommInt, mpi::comm_create_kind::comm_take_ownership);

    GameType gameType;
    parentComm.recv(0, as_integer(MPITag::GameType), gameType);
    PlayerId playerId;
    parentComm.recv(0, as_integer(MPITag::PlayerId), playerId);
    int depth;
    parentComm.recv(0, as_integer(MPITag::Depth), depth);

    Minimax minimax(depth, 0);

    std::shared_ptr<Game> game;
    std::shared_ptr<GameState> state;
    std::vector<std::shared_ptr<Move>> initMoves;

    // ToDo: fix this
    std::vector<TicTacToeMove> moves;

    switch (gameType)
    {
        case GameType::TicTacToe:
        default:
            game = std::make_shared<TicTacToe>(true, true);
            parentComm.recv(0, as_integer(MPITag::State), *state);
            parentComm.recv(0, as_integer(MPITag::Moves), moves);

            for (auto move : moves)
            {
                initMoves.emplace_back(&move);
            }

            break;
    }

    int bestScoreDiff = playerId == PlayerId::Player1 ? INT_MIN : INT_MAX;
    std::shared_ptr<Move> bestMove;
    std::shared_ptr<GameState> stateCpy;
    int currScoreDiff;
    for (auto move : initMoves)
    {
        *stateCpy = *state;
        bool isTurnOver = true;
        game->simulateMove(state.get(), move.get(), playerId, isTurnOver);

        if (playerId == PlayerId::Player1)
        {
            if (!isTurnOver)
            {
                minimax.getBestMove(game.get(), state.get(), gameType, PlayerId::Player1, currScoreDiff);
            }
            else
            {
                minimax.getBestMove(game.get(), state.get(), gameType, PlayerId::Player2, currScoreDiff);
            }
        }
        else
        {
            if (!isTurnOver)
            {
                minimax.getBestMove(game.get(), state.get(), gameType, PlayerId::Player2, currScoreDiff);
            }
            else
            {
                minimax.getBestMove(game.get(), state.get(), gameType, PlayerId::Player1, currScoreDiff);
            }
        }

        if ((playerId == PlayerId::Player1 && currScoreDiff > bestScoreDiff) || (playerId == PlayerId::Player2 && currScoreDiff < bestScoreDiff))
        {
            bestMove = move;
            bestScoreDiff = currScoreDiff;
        }

        *state = *stateCpy;
    }

    TicTacToeMove tttBestMove = *(dynamic_cast<TicTacToeMove*>(bestMove.get()));

    parentComm.send(0, as_integer(MPITag::BestMove), tttBestMove);
    parentComm.send(0, as_integer(MPITag::Score), bestScoreDiff);

    return 0;
}