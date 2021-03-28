#pragma once

#include "GameState.hpp"

class TicTacToeState : public GameState
{
	public:
		std::vector<std::vector<char>> board;
		TicTacToeState();
		void print();
		void printLine();
};