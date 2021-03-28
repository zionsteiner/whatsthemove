#pragma once
#include "GameState.hpp"
#include "Move.hpp"

#include <memory>
#include <vector>

/* 
 * PROBLEM 1: getMoves, getGameState, simulateMove, etc have game-specific logic. We want them to inherit from a general game model and require them to implement
 * these methods, but also want them to be static s.t. Minimax child processes will not have to have access to an instantiated Game object to work. 
 * However, static methods cannot be overridden.
 * 
 * SOLUTION 1: We can have each Minimax child process instantiate a Game object and only have it use const methods to process logic.
 *      PROBLEM: How to communicate to child process what Game implementation to instantiate?
 *      SOLUTION: virtual Enum getGameId()
 *          PROBLEM: how do library users add their own Game model to the enum at compile time?
 * 
 * SOLUTION 2 (BEST BET): Each Game implementation redefines the static game logic methods and getBestMove() is templated on Game
 *      PROBLEM: How to communicate to child process what Game implementation to instantiate?
 */

struct GameConfig
{
};

class Game
{
  private:
    GameState state;
    std::uint8_t currPlayerId;

  public:

    virtual std::shared_ptr<GameState> getGameState() { return std::make_shared<GameState>(state); }
    virtual std::vector<std::shared_ptr<Move>> getMoves(GameState& state, int player_id) const = 0;
    virtual void simulateMove(GameState& state, Move& move, int player_id) const = 0;
    virtual std::vector<int> scoreGameState(GameState& state) const = 0;
    virtual bool isGameOver(GameState& state) const = 0;
    virtual void nextTurn() = 0;
    virtual void play() = 0;
    std::uint8_t getCurrPlayerId() const { return currPlayerId; }

    virtual ~Game(){};
};
