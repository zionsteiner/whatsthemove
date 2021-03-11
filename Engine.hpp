#pragma once

#include "GameState.hpp"
#include "Move.hpp"

class Engine 
{
    public:
        virtual Move getBestMove(GameState* state, int depth) = 0;
};