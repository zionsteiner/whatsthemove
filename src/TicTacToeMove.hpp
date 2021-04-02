#pragma once

#include "Move.hpp"

class TicTacToeMove : public Move
{
	int xCoor, yCoor;
	public:
		TicTacToeMove();
		// do I need these '= 0's \|/
		int getX() = 0;
		int getY() = 0;
		void setMove(int x, int y);
		void setMoveFromUser();
};
