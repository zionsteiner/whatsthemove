#pragma once
#include "Game.hpp"
#include "Move.hpp"
#include "GameState.hpp"

class TicTacToe : public Game
{

  private:
    GameState state;

  public:
    TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman);

    GameState getState() const { return state; };

    void nextTurn() = 0;

    virtual std::vector<Move> getMoves(GameState& state, int player_id) const;

    virtual void simulateMove(GameState& state, Move& move, int player_id) const;

    virtual std::vector<int> scoreState(GameState& state) const = 0;

    virtual bool isGameOver(GameState& state) const = 0;
};
