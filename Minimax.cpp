#include "Minimax.hpp"

#include <boost/mpi.hpp>
#include <mpi.h>

namespace mpi = boost::mpi;

Move Minimax::getBestMove(Game& game, std::uint16_t depth, std::uint16_t nProcesses)
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
			mpi_recv(&move, ANY_SRC)
			if move > myBestMove:
				myBestMove = move

		return myBestMove;

	else:
		simulate()
		report()
	*/

    mpi::environment env;
    mpi::communicator world;

    if (world.rank() == 0)
    {
        // Get initial moves
        std::vector<Move> moves = game.getMoves(game.getState(), game.getCurrPlayerId());
    }
};

Move Minimax::min(Game& game, GameState& state, std::uint16_t depth)
{

}

Move Minimax::max(Game& game, GameState& state, std::uint16_t depth)
{

}
