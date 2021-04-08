#pragma once

#include "Move.hpp"

class Player
{
public:
    virtual Move* getMove(Game* game, std::vector<Move*> moves) = 0;
};
