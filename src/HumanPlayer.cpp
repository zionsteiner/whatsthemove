#include "HumanPlayer.hpp"

#include "Game.hpp"
#include "Move.hpp"

#include <iostream>

std::shared_ptr<Move> HumanPlayer::getMove(const Game* game, std::vector<std::shared_ptr<Move>> moves)
{
    while (true)
    {
        std::cout << "Please enter the move you'd like to make." << std::endl;
        for (int i = 0; i < moves.size(); i++)
        {
            printf("%d: %s\n", i + 1, moves[i]->toString().c_str());
        }

        int choice;
        std::cin >> choice;
        if (choice < 1 || choice > moves.size())
        {
            std::cout << "You have entered an invalid choice. Please try again." << std::endl;
        }
        else
        {
            return moves[choice - 1];
        }
    }
}
