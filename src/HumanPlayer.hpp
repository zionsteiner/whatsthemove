#pragma once

#include "Player.hpp"

class HumanPlayer : public Player
{
	public:
		Move* getMove() = 0;
		int getX() = 0;
		int getY() = 0;



};




