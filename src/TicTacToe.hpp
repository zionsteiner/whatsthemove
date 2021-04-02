#pragma once
#include "Game.hpp"
#include "TicTacToeState.hpp"
#include "TicTacToeMove.hpp"
#include "Player.hpp"

class TicTacToe : public Game
{

  private:
    TicTacToeState state;
    Player player1;
    Player player2;

  public:
    TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman);

    void nextTurn();

    void play();

    std::vector<std::shared_ptr<Move>> getMoves(GameState& state, int player_id) const;

    char getXOrO(int player_id) const;

    void simulateMove(GameState& state, Move& move, int player_id) const;

    std::vector<int> scoreGameState(GameState& state) const;

    bool validMove(GateState&, Move& move) const;

    char isGameOver(GameState& state) const;
};
