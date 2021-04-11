#include "TicTacToe.hpp"

#include "EnginePlayer.hpp"
#include "HumanPlayer.hpp"
#include "Minimax.hpp"

#include <iostream>

// ToDo: make sure all overriding methods match base Game class signatures

TicTacToe::TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman)
{
    // Create player classes (engine player and human player)
    state = std::make_shared<TicTacToeState>();

    if (isPlayerOneHuman)
    {
        player1 = std::make_unique<HumanPlayer>();
    }
    else
    {
        player1 = std::make_unique<EnginePlayer>(new Minimax(10, 0), GameType::TicTacToe);
    }

    if (isPlayerTwoHuman)
    {
        player2 = std::make_unique<HumanPlayer>();
    }
    else
    {
        player2 = std::make_unique<EnginePlayer>(new Minimax(10, 0), GameType::TicTacToe);
    }

    currPlayerId = PlayerId::Player1;
}

std::vector<std::shared_ptr<Move>> TicTacToe::getMoves(GameState* state, PlayerId player_id) const
{
    std::vector<std::shared_ptr<Move>> moves;

    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tttState->board[i][j] == '.')
            {
                moves.push_back(std::make_shared<TicTacToeMove>(i, j));
            }
        }
    }

    return moves;
}

char TicTacToe::getXOrO(PlayerId player_id) const
{
    if (player_id == PlayerId::Player1)
    {
        return 'X';
    }
    return 'O';
}

void TicTacToe::simulateMove(GameState* state, Move* move, PlayerId playerId, bool& isTurnOver) const
{
    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);
    TicTacToeMove* tttMove = dynamic_cast<TicTacToeMove*>(move);
    char moveValue = getXOrO(playerId);
    tttState->board[tttMove->getX()][tttMove->getY()] = moveValue;
    isTurnOver = true;
}

std::vector<int> TicTacToe::scoreGameState(GameState* state) const
{
    WinnerId stateWinnerId;
    isGameOver(state, stateWinnerId);

    if (stateWinnerId == WinnerId::Player1)
    {
        std::vector<int> scores{ 1, -1 };
        return scores;
    }
    else if (stateWinnerId == WinnerId::Player2)
    {
        std::vector<int> scores{ -1, 1 };
        return scores;
    }
    std::vector<int> scores{ 0, 0 };
    return scores;
}

// ToDo: should return bool
bool TicTacToe::isGameOver(GameState* state, WinnerId& winner) const
{

    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);

    for (int i = 0; i < 3; i++)
    {
        if (tttState->board[i][0] != '.' && tttState->board[i][0] == tttState->board[i][1] && tttState->board[i][0] == tttState->board[i][2])
        {
            if (tttState->board[i][0] == 'X')
            {
                winner = WinnerId::Player1;
            }
            else
            {
                winner = WinnerId::Player2;
            }
            return true;
        }
        if (tttState->board[0][i] != '.' && tttState->board[0][i] == tttState->board[1][i] && tttState->board[0][i] == tttState->board[2][i])
        {
            if (tttState->board[0][i] == 'X')
            {
                winner = WinnerId::Player1;
            }
            else
            {
                winner = WinnerId::Player2;
            }
            return true;
        }
    }

    for (int i = 0; i < 3; i += 2)
    {

        if (tttState->board[0][i] != '.' && tttState->board[0][i] == tttState->board[1][1] && tttState->board[0][i] == tttState->board[2][2 - i])
        {

            if (tttState->board[0][i] == 'X')
            {
                winner = WinnerId::Player1;
            }
            else
            {
                winner = WinnerId::Player2;
            }
            return true;
        }
    }

    int nOpenBoxes = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tttState->board[i][j] == '.')
            {
                nOpenBoxes++;
            }
        }
    }

    if (nOpenBoxes == 1)
    {
        winner = WinnerId::Tie;
        return true;
    }
    else
    {
        winner = WinnerId::None;
        return false;
    }
}

// ToDo: the game already knows who currPlayer is by currPlayerId
void TicTacToe::nextTurn()
{
    
    bool isTurnOver = false;
    while (!isTurnOver)
    {
	printPlayer(currPlayerId);
        std::shared_ptr<Move> move = getPlayer(currPlayerId)->getMove(this, getMoves(state.get(), currPlayerId));
        simulateMove(state.get(), move.get(), currPlayerId, isTurnOver);
        if (isTurnOver)
        {
            currPlayerId = currPlayerId == PlayerId::Player1 ? PlayerId::Player2 : PlayerId::Player1;
        }
    }
}

void TicTacToe::play()
{
    currPlayerId = PlayerId::Player1;
    WinnerId winner = WinnerId::None;
    std::cout << "Game Begins" << std::endl;
    while (!isGameOver(state.get(), winner))
    {
        state->print();
        nextTurn();
    }

    state->print();

    if (winner == WinnerId::Player1)
    {
        std::cout << "Player 1 has won the game." << std::endl;
    }
    else if (winner == WinnerId::Player2)
    {
        std::cout << "Player 2 has won the game." << std::endl;
    }
    else
    {
        std::cout << "The game ended in a tie." << std::endl;
    }
    // Check to see if each player is human or not, then run next turn
}
