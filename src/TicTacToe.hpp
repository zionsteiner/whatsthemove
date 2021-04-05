#pragma once
#include "Game.hpp"
#include "TicTacToeState.hpp"
#include <memory>

class TicTacToe : public Game
{
  public:
    TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman);

    void nextTurn();

    void play();

    std::vector<std::shared_ptr<Move>> getMoves(GameState& state, int player_id) const;

    char getXOrO(int player_id) const;

    void simulateMove(GameState& state, Move& move, int player_id) const;

    std::vector<int> scoreGameState(GameState& state) const;

    bool isValidMove(GameState&, Move& move) const;

    char isGameOver(GameState& state) const;
};
