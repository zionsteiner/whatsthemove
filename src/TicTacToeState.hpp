#pragma once

#include "GameState.hpp"

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>

class TicTacToeState : public GameState
{
  private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<GameState>(*this);
        ar& board;
    }

    TicTacToeState(std::vector<std::vector<char>> board) :
        board(board) {}

  public:
    std::vector<std::vector<char>> board;
    TicTacToeState();
    void print() const;
    void printLine() const;
};
