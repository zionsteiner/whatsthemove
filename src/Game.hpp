#pragma once
#include "GameState.hpp"
#include "Move.hpp"
#include "Player.hpp"

#include <memory>
#include <vector>
#include <string>
#include <iostream>
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

class Player;

struct GameConfig
{
};

enum class GameType
{
    TicTacToe
};

enum class PlayerId
{
    Player1,
    Player2
};

namespace boost
{
    namespace serialization
    {

        template <class Archive>
        void serialize(Archive& ar, PlayerId& p, const unsigned int version)
        {
            ar& p;
        }
    } // namespace serialization
} // namespace boost

enum class WinnerId
{
    Player1,
    Player2,
    Tie,
    None
};

namespace boost
{
    namespace serialization
    {

        template <class Archive>
        void serialize(Archive& ar, WinnerId& w, const unsigned int version)
        {
            ar& w;
        }
    } // namespace serialization
} // namespace boost

class Game
{
  protected:
    std::shared_ptr<GameState> state;
    PlayerId currPlayerId;
    WinnerId winnerId;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;

  public:
    Game() = default;
    virtual std::shared_ptr<GameState> getGameState() const { return state; }
    virtual std::vector<std::shared_ptr<Move>> getMoves(GameState* state, PlayerId playerId) const = 0;
    virtual void simulateMove(GameState* state, Move* move, PlayerId player_id, bool& isTurnOver) const = 0;
    virtual std::vector<int> scoreGameState(GameState* state) const = 0;
    virtual bool isGameOver(GameState* state, WinnerId& winner) const = 0;
    virtual void nextTurn() = 0;
    virtual void play() = 0;
    PlayerId getCurrPlayerId() const { return currPlayerId; }
    WinnerId getWinnerId() const { return winnerId; }

    std::shared_ptr<Player> getPlayer(PlayerId playerId) const
    {
        if (playerId == PlayerId::Player1)
        {
            return player1;
        }
        else
        {
            return player2;
        }
    }

     void printPlayer(PlayerId playerId) const {
	if (playerId == PlayerId::Player1) {
	    std::cout << "Player 1 Turn: " << std::endl;
	}
	else {
	    std::cout << "Player 2 Turn: " << std::endl;
	}

     }

    virtual ~Game(){};
};
