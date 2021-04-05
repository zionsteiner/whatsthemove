#pragma once

#include "Move.hpp"
#include <memory>

class Player
{
public:
    virtual std::shared_ptr<Move> getMove(Game* game) = 0;
};
