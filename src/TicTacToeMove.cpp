#include "TicTacToeMove.hpp"

#include "Game.hpp"

TicTacToeMove::TicTacToeMove(int x, int y)
{
    xCoor = x;
    yCoor = y;
}

int TicTacToeMove::getX() const
{
    return xCoor;
}

int TicTacToeMove::getY() const
{
    return yCoor;
}

std::string TicTacToeMove::toString() const
{
    return "X: " + std::to_string(xCoor) + ", Y: " + std::to_string(yCoor);
}
