#pragma once

#include "Engine.hpp"
#include "GameState.hpp"
#include "Move.hpp"

class Minimax: Engine
{
    Move getBestMove(GameState* state, int depth);
};