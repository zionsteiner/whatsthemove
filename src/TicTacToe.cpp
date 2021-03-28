#include "TicTacToe.hpp"
#include "HumanPlayer.hpp"

TicTacToe::TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman)
{
	// Create player classes (engine player and human player)
	TicTacToeState state ();
	// Dynamic cast?
	if (isPlayerOneHuman) {
		HumanPlayer player1();
	}else {
		EnginePlayer player1();
	}

	if (isPlayerTwoHuman) {
		HumanPlayer player2();
	}else {
		EnginePlayer player2();
}

	
}

std::vector<Move> TicTacToe::getMoves(GameState& state, int player_id) const
{
	std::vector<Move> moves;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (state.board[i][j] == '.') {
				TicTacToeMove newMove (i, j);
				moves.push_back(newMove);
			}
		}
	}
	return moves;
}

char TicTacToe::getXOrO(int player_id) {
	if (player_id == 1) {
		return 'X';
}
	return 'O';
}

void TicTacToe::simulateMove(GameState& state, Move& move, int player_id) const
{
	char moveValue = getXOrO(player_id);
	state.board[move.getX()][move.getY()] = moveValue;
}

std::vector<int> TicTacToe::scoreGameState(GameState& state) const
{
	char gameOver = isGameOver(state);
	if (gameOver == 'X') {
		std::vector<int> scores {1, -1};
		return scores;
	}else if (gameOver == 'O') {
		std::vector<int> scores {-1, 1};
		return scores;
	}
	std::vector<int> scores {0, 0};
	return scores;

}

bool validMove(GameState& state, Move& move) const
{
	return state.board[move.getX()][move.getY()] == '.';
}

char TicTacToe::isGameOver(GameState& state) const
{
	for (int i = 0; i < 3; i++) {
		if (state.board[i][0] != '.' && state.board[i][0] == state.board[i][1] && state.board[i][0] == state.board[i][2]) {
			return state.board[i][0];
		}
		if (state.board[i][0] != '.' && state.board[0][i] == state.board[1][i] && state.board[0][i] == state.board[2][i]) {
			return state.board[0][i];
		}
	}

	for (int i = 0; i < 3; i+= 2) {
		
		if (state.board[0][i] != '.' && state.board[0][i] == state.board[1][1] && state.board[0][i] == state.board[2][2-i]) {
			return state.board[0][0];
		}
	}

	return '.';

}

void makeMove(Move& move) {
	simulateMove(state, move);
}

void TicTacToe::nextTurn(Player* playerPointer)
{
	Player player = *playerPointer;
	bool isValidMove = false;
	TicTacToeMove move ();
	while (!isValidMove) {
		player.getMove(move);
		isValidMove = validMove(state, move);
		if (!isValidMove) {
			cout << "You have entered an invalid move. Please try again." << endl;
		}
	}
	makeMove(move);

}

void TicTacToe::play()
{
	char gameOver = '.';
	Player* player = &player1;
	bool playerOneNextTurn = true;
	while (gameOver == '.') {
		nextTurn(player);
		gameOver = isGameOver(state);
		if (playerOneTurn) {
			player = &player1;
		}else {
			player = &player2;
		}
		// Print game board
		state.print();
	}
	if (gameOver == 'X') {
		cout << "Player 1 has won the game." << endl;
	}else{
		cout << "Player 2 has won the game." << endl;
	}
	// Check to see if each player is human or not, then run next turn
}