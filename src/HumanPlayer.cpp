#include "HumanPlayer.hpp"

#include "Move.hpp"

Move* HumanPlayer::getMove(Game* game, std::vector<Move*> moves)
{
	while (1) {
		cout << "Please enter the move you'd like to make." << endl;
		for (int i = 0; i < moves.size(); i++) {
			TicTacToeMove* tttMove = dynamic_cast<TicTacToeMove*>(moves[i]);
			cout << i + 1 << ". X: " << tttMove.getX() << ", Y: " << tttMove.getY() << endl;
		}
		int choice;
		cin >> choice;
		if (choice < 1 || choice > moves.size()) {
			cout << "You have entered an invalid choice. Please try again." << endl;
	 	}else {
			return moves[i - 1];
		}
		
	}
}
