#pragma once

#include "Move.hpp"

class Player
{
    public:
        virtual std::shared_ptr<Move> getMove(Game* game) = 0;
};
