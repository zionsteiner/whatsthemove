#pragma once

#include "Game.hpp"
#include "Move.hpp"
#include "Game.hpp"

#include <cstdint>

class Engine
{
  public:
    virtual Move getBestMove(Game& game, std::uint16_t depth, std::uint16_t nProcesses) = 0;
};