#include "TicTacToe.hpp"

int main(int argc, char** argv)
{
    // Parse game options from argv
    // Make GameConfig
    // Init Game object
    std::string player1Human;
    std::string player2Human;
    bool player1HumanBool = false;
    bool player2HumanBool = false;
    bool validInput = false;
    while (!validInput) {
        std::cout << "Is player 1 human (y/n)?" << std::endl;
	std::cin >> player1Human;
	char firstChar = player1Human[0];
	validInput = true;
	if (firstChar == 'y') {
	    player1HumanBool = true;
	}
	else if (firstChar == 'n') {
	    player1HumanBool = false;
	}else {
	    validInput = false;
	}
    }
    validInput = false; 
    while (!validInput) {
        std::cout << "Is player 2 human (y/n)?" << std::endl;
	std::cin >> player2Human;
	char firstChar = player2Human[0];
	validInput = true;
	if (firstChar == 'y') {
	    player2HumanBool = true;
	}
	else if (firstChar == 'n') {
	    player2HumanBool = false;
	}else {
	    validInput = false;
	}
    }
    TicTacToe game(player1HumanBool, player2HumanBool);
    game.play();
}
