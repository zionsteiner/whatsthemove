#include "Minimax.hpp"

#include "TicTacToe.hpp"

#include <boost/mpi.hpp>
#include <boost/serialization/vector.hpp>
#include <mpi.h>

namespace mpi = boost::mpi;

std::shared_ptr<Move> Minimax::getBestMove(const Game* game, GameState* state, GameType gameType, PlayerId playerId, int& score)
{
    // How is it run?
    // mpiexec -np x tictactoe
    /* 
	* 
	* PROBLEM: If static methods cannot be made virtual, they must be instance virtual. 
	* Each process needs access to game object, so we need to initialize one for each process.
	* Only the parent process instance needs to maintain state, the others are used for their methods.
	* 
	* PROBLEM: We want a single process to run the game init and logic. We only want multi-process for the gameEngine.
	* Ideally, only Minimax knows about this. However, if the entry point is main, main will have to know about it.
	* Engine.getBestMove() would need to be called for each process each time it is called from the parent. How to
	* do this inside main if we only run a single line of game logic execution that other processes never enter?
	* 
	* Ugly solution:
	*	* Write main as if it doesn't know about MPI and is single-process. With n processes, n games will be initialized.
	*	* On AIPlayer turn, parent process AIPlayer calls Engine.getBestMove(), which sends moves to other processes to
	*	* compute. If .getBestMove() is called from child process, recv moves to computer and send back.
	* 
	*	* PROBLEM: If we init a game object for each process with a human and AI player, the other processes will not get
	*	human input.
	*	
	* 
	* Alternatives:
	*	* MPI_Comm_Spawn (best bet)
	*	* from main, start engine in its own process and somehow get return move
	* 
	if rank == 0:
		# Get initial moves

		moves = game.getMoves()
		nMoves = len(moves)
		q = queue<Move>(moves)

		# Distribute moves
		movesPerProcess = q.size() / nProcesses
		myMoves = [q.pop() for _ in range(movesPerProcess)]
		for (i+1 in nProcesses):
			for (j in movesPerProcess):
				MPI_Send(q.pop(), i)
		i = 1;
		while(!q.empty):
			mpi_send(q.pop(), i++)
			i %= size;
			if (i == 0)
				i++
		
		# simulate
		myBestMove = null
		for move in myMoves:
			currBestMove = min/max(game, state, move)
			if currBestMove > myBestMove:
				myBestMove = currBestMove


		# collect results
		for i in range(nMoves - myMoves):
			Move move
			mpi_recv(*move, ANY_SRC)
			if move > myBestMove:
				myBestMove = move

		return myBestMove;

	else:
		simulate()
		report()
	*/

    MPI_Comm parentComm;
    MPI_Comm_get_parent(&parentComm);

    std::shared_ptr<Move> bestMove;
    int bestScoreDiff = playerId == PlayerId::Player1 ? INT_MIN : INT_MAX;

    if (parentComm == MPI_COMM_NULL)
    {
        // Get initial moves
        std::vector<std::shared_ptr<Move>> moves = game->getMoves(state, game->getCurrPlayerId());

        int nChildren;
        MPI_Comm_remote_size(childComm, &nChildren);
        int movesPerProcess = moves.size() / (nChildren + 1);
        int remainder = moves.size() - movesPerProcess * (nChildren + 1);

        // Get own moves to test
        std::vector<std::shared_ptr<Move>> localMoves;
        for (int i = 0; i < (movesPerProcess + remainder); ++i)
        {
            localMoves.push_back(moves.back());
            moves.pop_back();
        }

        // Distribute moves
        std::vector<std::shared_ptr<Move>> remoteMoves;
        for (int i = 0; i < nChildren; ++i)
        {
            for (int j = 0; j < movesPerProcess; ++j)
            {
                remoteMoves.push_back(moves.back());
                moves.pop_back();
            }

            switch (gameType)
            {
                case GameType::TicTacToe:
                    childComm.send(i, as_integer(MPITag::GameType), gameType);

                    std::vector<TicTacToeMove> tttMoves;
                    for (auto move : remoteMoves)
                    {
                        tttMoves.push_back(*dynamic_cast<TicTacToeMove*>(move.get()));
                    }

                    childComm.send(i, as_integer(MPITag::Moves), tttMoves);
                    break;
            }

            childComm.send(i, as_integer(MPITag::State), *state);
            childComm.send(i, as_integer(MPITag::PlayerId), playerId);
            childComm.send(i, as_integer(MPITag::Depth), depth);

            remoteMoves.clear();
        }

        // Simulate
        int currScoreDiff;

        std::shared_ptr<GameState> stateCpy;
        for (auto move : localMoves)
        {
            // Copy state
            stateCpy = state->clone();
            bool isTurnOver = true;
            game->simulateMove(state, move.get(), playerId, isTurnOver);

            if (playerId == PlayerId::Player1)
            {
                if (!isTurnOver)
                {
                    // Go again
                    max(game, state, currScoreDiff, depth);
                }
                else
                {
                    min(game, state, currScoreDiff, depth);
                }
            }
            else
            {
                if (!isTurnOver)
                {
                    // Go again
                    min(game, state, currScoreDiff, depth);
                }
                else
                {
                    max(game, state, currScoreDiff, depth);
                }
            }

            // Check if better move
            if ((playerId == PlayerId::Player1 && currScoreDiff > bestScoreDiff) || (playerId == PlayerId::Player2 && currScoreDiff < bestScoreDiff))
            {
                bestMove = move;
                bestScoreDiff = currScoreDiff;
            }

            // Restore state
            *state = *stateCpy;
        }

        // Collect results
        int remoteScoreDiff;
        for (int i = 0; i < nChildren; ++i)
        {
            std::shared_ptr<Move> remoteBestMove;

            childComm.recv(i, as_integer(MPITag::BestMove), *remoteBestMove);
            childComm.recv(i, as_integer(MPITag::Score), remoteScoreDiff);

            if ((playerId == PlayerId::Player1 && remoteScoreDiff > bestScoreDiff) || (playerId == PlayerId::Player2 && remoteScoreDiff < bestScoreDiff))
            {
                bestMove = remoteBestMove;
                bestScoreDiff = remoteScoreDiff;
            }
        }
    }
    else
    {
        if (playerId == PlayerId::Player1)
        {
            bestMove = max(game, state, bestScoreDiff, depth);
        }
        else
        {
            bestMove = min(game, state, bestScoreDiff, depth);
        }
    }

    score = bestScoreDiff;

    return bestMove;
}

// ToDo: figure out when to make a copy of state and scoreDiff and when to set reference value
// P2 is min
std::shared_ptr<Move> Minimax::min(const Game* game, GameState* state, int& scoreDiff, std::uint16_t depth)
{
    int bestScoreDiff = INT_MAX;

    WinnerId winnerId;
    bool isGameOver = game->isGameOver(state, winnerId);

    std::vector<int> scores = game->scoreGameState(state);
    scoreDiff = scores[0] - scores[1];

    if (isGameOver || depth == 0)
    {
        return nullptr;
    }

    // Recurse
    std::vector<std::shared_ptr<Move>> moves = game->getMoves(state, PlayerId::Player2);
    std::shared_ptr<Move> bestMove;
    std::shared_ptr<GameState> stateCpy;
    int currScoreDiff;
    for (auto move : moves)
    {
        stateCpy = state->clone();
        bool isTurnOver;

        game->simulateMove(state, move.get(), PlayerId::Player2, isTurnOver);

        if (!isTurnOver)
        {
            min(game, state, currScoreDiff, depth - 1);
        }
        else
        {
            max(game, state, currScoreDiff, depth - 1);
        }

        if (currScoreDiff < bestScoreDiff)
        {
            bestScoreDiff = currScoreDiff;
            bestMove = move;
        }

        *state = *stateCpy;
    }

    scoreDiff = bestScoreDiff;

    return bestMove;
}

// P1 is max
std::shared_ptr<Move> Minimax::max(const Game* game, GameState* state, int& scoreDiff, std::uint16_t depth)
{
    int bestScoreDiff = INT_MIN;

    WinnerId winnerId;
    bool isGameOver = game->isGameOver(state, winnerId);

    std::vector<int> scores = game->scoreGameState(state);
    scoreDiff = scores[0] - scores[1];

    if (isGameOver || depth == 0)
    {
        return nullptr;
    }

    // Recurse
    std::vector<std::shared_ptr<Move>> moves = game->getMoves(state, PlayerId::Player1);
    std::shared_ptr<Move> bestMove;
    std::shared_ptr<GameState> stateCpy;
    int currScoreDiff;
    for (auto move : moves)
    {
        stateCpy = state->clone();
        bool isTurnOver;
        game->simulateMove(state, move.get(), PlayerId::Player1, isTurnOver);

        if (!isTurnOver)
        {
            max(game, state, currScoreDiff, depth - 1);
        }
        else
        {
            min(game, state, currScoreDiff, depth - 1);
        }

        if (currScoreDiff > bestScoreDiff)
        {
            bestScoreDiff = currScoreDiff;
            bestMove = move;
        }

        *state = *stateCpy;
    }

    scoreDiff = bestScoreDiff;

    return bestMove;
}

void Minimax::spawnWorkers()
{
    if (nWorkers > 0)
    {
        MPI_Comm childCommInt = static_cast<MPI_Comm>(childComm);
        MPI_Comm_spawn("minimax_worker", MPI_ARGV_NULL, nWorkers, MPI_INFO_NULL, 0, MPI_COMM_SELF, &childCommInt, MPI_ERRCODES_IGNORE);
    }
}
