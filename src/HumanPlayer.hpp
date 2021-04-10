#pragma once

#include "Player.hpp"

class HumanPlayer : public Player
{
  public:
    std::shared_ptr<Move> getMove(const Game* game, std::vector<std::shared_ptr<Move>> moves);
};
