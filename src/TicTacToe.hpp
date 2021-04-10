#pragma once
#include "Game.hpp"
#include "Player.hpp"
#include "TicTacToeMove.hpp"
#include "TicTacToeState.hpp"

#include <memory>

class TicTacToe : public Game
{
  public:
    TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman);

    void nextTurn();

    void play();

    std::vector<std::shared_ptr<Move>> getMoves(GameState* state, PlayerId player_id) const;

    char getXOrO(PlayerId player_id) const;

    void simulateMove(GameState* state, Move* move, PlayerId player_id, bool& thisPlayerTurnOver) const;

    std::vector<int> scoreGameState(GameState* state) const;

    bool isGameOver(GameState* state, WinnerId& winner) const;
};
