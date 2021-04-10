#include "TicTacToeState.hpp"

#include <iostream>

TicTacToeState::TicTacToeState()
{
    for (int i = 0; i < 3; i++)
    {
        std::vector<char> row{ '.', '.', '.' };
        board.push_back(row);
    }
}

void TicTacToeState::printLine() const
{
    for (int i = 0; i < 7; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

void TicTacToeState::print() const
{
    for (int i = 0; i < 3; i++)
    {
        printLine();
        for (int j = 0; j < 3; j++)
        {
            std::cout << "|" << board[i][j];
        }
        std::cout << "|" << std::endl;
    }
    printLine();
}
