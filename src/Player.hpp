#pragma once

#include "Move.hpp"
#include <memory>

class Player
{
public:
    virtual Move* getMove(Game* game, std::vector<Move*> moves) = 0;
};
