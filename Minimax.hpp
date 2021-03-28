#pragma once

#include "Engine.hpp"
#include "GameState.hpp"

#include <cstdint>

class Minimax : public Engine
{
    Move getBestMove(Game& game, std::uint16_t depth, std::uint16_t nProcesses);
    Move min(Game& game, GameState& state, std::uint16_t depth);
    Move max(Game& game, GameState& state, std::uint16_t depth);
};