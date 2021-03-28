#pragma once

#include "Engine.hpp"
#include "GameState.hpp"

#include <cstdint>

class Minimax : public Engine
{
private:
    std::shared_ptr<Move> min(Game* game, GameState* state, std::uint16_t depth);
    std::shared_ptr<Move> max(Game* game, GameState* state, std::uint16_t depth);
public:
    std::shared_ptr<Move> getBestMove(Game* game, GameState* state, Move* move, std::uint16_t depth, std::uint16_t nProcesses);
};