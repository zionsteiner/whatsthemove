#include "TicTacToe.hpp"

#include "HumanPlayer.hpp"
#include "EnginePlayer.hpp"

// ToDo: make sure all overriding methods match base Game class signatures

TicTacToe::TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman):
{
    // Create player classes (engine player and human player)
    TicTacToeState state();

    if (isPlayerOneHuman)
    {
        player1 = std::make_unique<HumanPlayer>();
    }
    else
    {
        player1 = std::make_unique<EnginePlayer>();
    }

    if (isPlayerTwoHuman)
    {
        player2 = std::make_unique<HumanPlayer>();
    }
    else
    {
        player2 = std::make_unique<EnginePlayer>();
    }

    currPlayerId = PlayerId::Player1;
}

std::vector<std::shared_ptr<Move>> TicTacToe::getMoves(GameState& state, int player_id) const
{
    std::vector<Move> moves;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state.board[i][j] == '.')
            {
                TicTacToeMove newMove(i, j);
                moves.push_back(newMove);
            }
        }
    }
    return moves;
}

char TicTacToe::getXOrO(int player_id)
{
    if (player_id == 1)
    {
        return 'X';
    }
    return 'O';
}

void TicTacToe::simulateMove(GameState& state, Move& move, int player_id) const
{
    char moveValue = getXOrO(player_id);
    state.board[move.getX()][move.getY()] = moveValue;
}

std::vector<int> TicTacToe::scoreGameState(GameState& state) const
{
    char gameOver = isGameOver(state);
    if (gameOver == 'X')
    {
        std::vector<int> scores{ 1, -1 };
        return scores;
    }
    else if (gameOver == 'O')
    {
        std::vector<int> scores{ -1, 1 };
        return scores;
    }
    std::vector<int> scores{ 0, 0 };
    return scores;
}

bool isValidMove(GameState& state, Move& move) const
{
    return state.board[move.getX()][move.getY()] == '.';
}

// ToDo: should return bool
char TicTacToe::isGameOver(GameState& state) const
{
    for (int i = 0; i < 3; i++)
    {
        if (state.board[i][0] != '.' && state.board[i][0] == state.board[i][1] && state.board[i][0] == state.board[i][2])
        {
            return state.board[i][0];
        }
        if (state.board[i][0] != '.' && state.board[0][i] == state.board[1][i] && state.board[0][i] == state.board[2][i])
        {
            return state.board[0][i];
        }
    }

    for (int i = 0; i < 3; i += 2)
    {

        if (state.board[0][i] != '.' && state.board[0][i] == state.board[1][1] && state.board[0][i] == state.board[2][2 - i])
        {
            return state.board[0][0];
        }
    }

    return '.';
}

void makeMove(Move& move)
{
    simulateMove(state, move);
}

// ToDo: the game already knows who currPlayer is by currPlayerId
void TicTacToe::nextTurn()
{
    // bool isTurnOver = false;
    // while (!isTurnOver) {
    //     move = player.getMove(game.getState(), game.getmoves())
    //     int scoreDiff;
    //     game.simulateMove(state, move, currPlayerId, isTurnOver)
    //     currPlayerId = currPlayerId == PlayerId::Player1 ? PlayerId::Player2 : PlayerId::Player1
    // }
    bool isisValidMove = false;
    TicTacToeMove move();
    while (!isisValidMove)
    {
        std::shared_ptr<TicTacToe> move = std::shared_ptr(player.getMove());
        isisValidMove = isValidMove(state, move);
        if (!isisValidMove)
        {
            cout << "You have entered an invalid move. Please try again." << endl;
        }
    }
    makeMove(move);
}

void TicTacToe::play()
{
    /* ToDo:
    * while(!isGameOver())
    * {
    *   nextTurn()
    * }
    *
    */

    char gameOver = '.';
    currPlayerId = PlayerId::Player1;
    bool playerOneNextTurn = true;
    while (gameOver == '.')
    {
        nextTurn();
        gameOver = isGameOver(state);
        if (playerOneTurn)
        {
            player = &player1;
        else
        {
            player = &player2;
        }
        }
        // Print game board
        state.print();
    }

    if (gameOver == 'X')
    {
        cout << "Player 1 has won the game." << endl;
    }
    else
    {
        cout << "Player 2 has won the game." << endl;
    }
    // Check to see if each player is human or not, then run next turn
}