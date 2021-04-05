#pragma once

#include "Move.hpp"

class TicTacToeMove : public Move
{
  private:
    int xCoor;
    int yCoor;

  public:
    TicTacToeMove();
    int getX();
    int getY();
    void setMove(int x, int y);
    void setMoveFromUser();
};