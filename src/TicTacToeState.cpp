#include "TicTacToeState.hpp"

// ToDo: add includes
// ToDo: boost serialize method
TicTacToeState::TicTacToeState()
{
    for (int i = 0; i < 3; i++)
    {
        std::vector<char> row{ '.', '.', '.' } board.push_back(row);
    }
}

void TicTacToeState::printLine()
{
    for (int i = 0; i < 7; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void TicTacToeState::print()
{
    for (int i = 0; i < 3; i++)
    {
        printLine();
        for (int j = 0; j < 3; j++)
        {
            cout << "|" << board[i][j];
        }
        cout << "|" << endl;
    }
    printLine();
}
