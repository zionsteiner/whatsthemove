#pragma once
#include "GameState.hpp"
#include "GameMove.hpp"
#include "Game.hpp"



class TicTacToe : public Game 
{

private:
	GameState state;

public:
	TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman);
	
	GameState* getState() = 0;

	void nextTurn() = 0;
	
	static std::vector<Move>* getMoves(GameState* state, int player_id) = 0;

	static void simulateMove(GameState* state, Move* move, int player_id ) = 0;

	static std::vector<int>* scoreState(GameState* state) = 0;

	static bool isGameOver(GameState* state) = 0;


	
};


