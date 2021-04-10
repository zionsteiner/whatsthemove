#pragma once

#include "Game.hpp"
#include "Move.hpp"

#include <cstdint>
#include <memory>

class Engine
{
  public:
    virtual std::shared_ptr<Move> getBestMove(const Game* game, GameState* state, GameType gameType, PlayerId playerId, int& score) = 0;
};