#pragma once
#include "Game.hpp"
#include "Move.hpp"

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <string>

class TicTacToeMove : public Move
{
  protected:
    int xCoor;
    int yCoor;

    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<Move>(*this);
        ar& xCoor;
        ar& yCoor;
    }

  public:
    TicTacToeMove() :
        xCoor(-1), yCoor(-1) {}
    TicTacToeMove(int x, int y);
    int getX() const;
    int getY() const;
    std::string toString() const;
};
