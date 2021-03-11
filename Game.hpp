#pragma once
#include "GameState.hpp"
#include "GameMove.hpp"

class Game 
{
	virtual static GameState* getState() = 0;

	virtual static std::vector<Move>* getMoves(GameState* state, int player_id) = 0;

	virtual static void simulateMove(GameState* state, Move* move, int player_id ) = 0;

	virtual static std::vector<int>* scoreState(GameState* state) = 0;

	virtual static bool isGameOver(GameState* state) = 0;

	virtual void nextTurn() = 0;

};


