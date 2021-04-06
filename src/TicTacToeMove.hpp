#pragma once
#include <boost/serialization/vector.hpp>
#include "Move.hpp"

class TicTacToeMove : public Move
{
  private:
    int xCoor;
    int yCoor;
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version);

  public:
    TicTacToeMove();
    int getX();
    int getY();
    void setMove(int x, int y);
    void setMoveFromUser();
};
