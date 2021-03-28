#pragma once

#include "Game.hpp"
#include "Move.hpp"
#include <memory>
#include <cstdint>

class Engine
{
  public:
    virtual std::shared_ptr<Move> getBestMove(Game* game, GameState* state, Move* move, std::uint16_t depth, std::uint16_t nProcesses) = 0;
};