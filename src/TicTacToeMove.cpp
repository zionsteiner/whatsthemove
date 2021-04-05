#include "TicTacToeMove.hpp"

// ToDo: boost serialize method
TicTacToeMove::TicTacToeMove() {}

int TicTacToeMove::getX()
{
    return xCoor;
}

int TicTacToeMove::getY()
{
    return yCoor;
}

void setMove(int x, int y)
{
    xCoor = x;
    yCoor = y;
}

/* ToDo: Because different players create moves differently,
 * move should not know about player. Player is responsible for constructing move 
 */
void setMoveFromUser()
{
    cout << "Enter the row which you'd like to mark [1-3]" << endl;
    cin >> xCoor;
    cout << "Enter the column which you'd like to mark [1-3]" << endl;
    cin >> yCoor;
}
