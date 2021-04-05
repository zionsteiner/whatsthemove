#pragma once

#include "Player.hpp"

class HumanPlayer : public Player
{
  public:
    Move* getMove();
    void promptUser();
    int getX();
    int getY();
};
