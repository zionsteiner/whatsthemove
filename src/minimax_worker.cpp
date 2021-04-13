#include "Minimax.hpp"
#include "TicTacToe.hpp"

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>
#include <mpi.h>

#define MCW MPI_COMM_WORLD

namespace mpi = boost::mpi;

// Change minimax.getBestMove() to be a template method that somehow knows what type to send to minimax_workers

void work(mpi::communicator& comm, GameType& gameType, Minimax& minimax);

// ToDo: eliminate all switches on class type
int main(int argc, char** argv)
{
    // ToDo: potential bug, idk what happens with multiple env objects in same process
    mpi::environment env;

    // Receive move from spawning process 0
    MPI_Comm parentCommInt;
    MPI_Comm_get_parent(&parentCommInt);
    mpi::communicator parentComm = mpi::communicator(parentCommInt, mpi::comm_create_kind::comm_take_ownership);

    int depth;
    parentComm.recv(0, as_integer(MPITag::Depth), depth);

    GameType gameType;
    parentComm.recv(0, as_integer(MPITag::GameType), gameType);

    Minimax minimax(gameType, depth, 0);

    while (true)
    {
        if (boost::optional<mpi::status> status = parentComm.iprobe(0, as_integer(MPITag::Start)))
        {
            parentComm.recv(0, as_integer(MPITag::Start));
            work(parentComm, gameType, minimax);
        }
        else if (boost::optional<mpi::status> status = parentComm.iprobe(0, as_integer(MPITag::Exit)))
        {
            parentComm.recv(0, as_integer(MPITag::Exit));
            break;
        }
    }

    return 0;
}

void work(mpi::communicator& comm, GameType& gameType, Minimax& minimax)
{
    PlayerId playerId;
    comm.recv(0, as_integer(MPITag::PlayerId), playerId);

    std::shared_ptr<Game> game;
    std::shared_ptr<GameState> state;
    std::vector<std::shared_ptr<Move>> initMoves;

    switch (gameType)
    {
        case GameType::TicTacToe:
            std::vector<TicTacToeMove> moves;
            TicTacToeState tttState;

            game = std::make_shared<TicTacToe>(true, true);

            comm.recv(0, as_integer(MPITag::State), tttState);
            state = tttState.clone();

            comm.recv(0, as_integer(MPITag::Moves), moves);
            for (auto move : moves)
            {
                initMoves.push_back(std::make_shared<TicTacToeMove>(move));
            }

            break;
    }

    int bestScoreDiff = playerId == PlayerId::Player1 ? INT_MIN : INT_MAX;
    std::shared_ptr<Move> bestMove;
    std::shared_ptr<GameState> stateCpy;
    int currScoreDiff;
    for (auto move : initMoves)
    {
        stateCpy = state->clone();
        bool isTurnOver = true;

        game->simulateMove(state.get(), move.get(), playerId, isTurnOver);

        if (playerId == PlayerId::Player1)
        {
            if (!isTurnOver)
            {
                minimax.getBestMove(state.get(), PlayerId::Player1, currScoreDiff);
            }
            else
            {
                minimax.getBestMove(state.get(), PlayerId::Player2, currScoreDiff);
            }
        }
        else
        {
            if (!isTurnOver)
            {
                minimax.getBestMove(state.get(), PlayerId::Player2, currScoreDiff);
            }
            else
            {
                minimax.getBestMove(state.get(), PlayerId::Player1, currScoreDiff);
            }
        }

        if ((playerId == PlayerId::Player1 && currScoreDiff > bestScoreDiff) || (playerId == PlayerId::Player2 && currScoreDiff < bestScoreDiff))
        {
            bestMove = move;
            bestScoreDiff = currScoreDiff;
        }

        state = stateCpy->clone();
    }

    switch (gameType)
    {
        case GameType::TicTacToe:
            TicTacToeMove tttBestMove = *(dynamic_cast<TicTacToeMove*>(bestMove.get()));
            comm.send(0, as_integer(MPITag::BestMove), tttBestMove);
            break;
    }

    comm.send(0, as_integer(MPITag::Score), bestScoreDiff);
}