#pragma once

#include "Game.hpp"
#include "Move.hpp"
#include "TicTacToe.hpp"

#include <cstdint>
#include <memory>

// ToDo: template on Game, make Move and State inner classes
class Engine
{
  protected:
    GameType gameType;
    std::shared_ptr<Game> game;

  public:
    Engine(GameType gameType) :
        gameType(gameType)
    {
        switch (gameType)
        {
            case GameType::TicTacToe:
                /* Must be true, otherwise will infinitely recurse.
                * This is also a circular dependency 
                * TicTacToe -> EnginePlayer -> Engine -> TicTacToe */
                game = std::make_shared<TicTacToe>(true, true);
        }
    }

    virtual ~Engine() {}

    virtual std::shared_ptr<Move> getBestMove(GameState* state, PlayerId playerId, int& score) = 0;
};