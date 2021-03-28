#pragma once
#include "Game.hpp"
#include "TicTacToeState.hpp"
#include "TicTacToeMove.hpp"

class TicTacToe : public Game
{

  private:
    TicTacToeState state;

  public:
    TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman);

    void nextTurn();

    void play();

    std::vector<std::shared_ptr<Move>> getMoves(GameState& state, int player_id) const;

    void simulateMove(GameState& state, Move& move, int player_id) const;

    std::vector<int> scoreGameState(GameState& state) const;

    bool isGameOver(GameState& state) const;
};
