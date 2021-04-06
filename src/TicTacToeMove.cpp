#include "TicTacToeMove.hpp"

// ToDo: boost serialize method
TicTacToeMove::TicTacToeMove(int x, int y) {
	xCoor = x;
	yCoor = y;
}

void serialize(Archive& ar, const unsigned int version) {
	ar& boost::serialization::base_object<ClassSerializationBase>(*this);
	ar& x;
	ar& y;
}

int TicTacToeMove::getX()
{
    return xCoor;
}

int TicTacToeMove::getY()
{
    return yCoor;
}

