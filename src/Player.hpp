#pragma once

#include "Game.hpp"
#include "Move.hpp"

#include <memory>
#include <vector>

class Game;

class Player
{
  public:
    virtual std::shared_ptr<Move> getMove(const Game* game, std::vector<std::shared_ptr<Move>> moves) = 0;
};