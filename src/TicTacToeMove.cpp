#include "TicTacToeMove.hpp"

TicTacToeMove::TicTacToeMove() {}

int TicTacToeMove::getX() {
	return xCoor;
}

int TicTacToeMove::getY() {
	return yCoor;
}

void setMove(int x, int y) {
	xCoor = x;
	yCoor = y;
}

void setMoveFromUser() {
	cout << "Enter the row which you'd like to mark [1-3]" << endl;
	cin >> xCoor;
	cout << "Enter the column which you'd like to mark [1-3]" << endl;
	cin >> yCoor;
}



