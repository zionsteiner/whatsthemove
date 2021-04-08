#include "TicTacToe.hpp"

#include "HumanPlayer.hpp"
#include "EnginePlayer.hpp"

// ToDo: make sure all overriding methods match base Game class signatures


TicTacToe::TicTacToe(bool isPlayerOneHuman, bool isPlayerTwoHuman)
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
    std::vector<std::shared_ptr<Move>> moves;

    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tttState->board[i][j] == '.')
            {
                moves.push_back(make_shared<TicTacToeMove>(i,j));
            }
        }
    }
    return moves;
}

char TicTacToe::getXOrO(PlayerId player_id)
{
    if (player_id == PlayerId::Player1)
    {
        return 'X';
    }
    return 'O';
}

void TicTacToe::simulateMove(GameState& state, Move& move, PlayerId player_id, bool& thisPlayerTurnOver) const
{
    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);
    TicTacToeMove* tttMove = dynamic_cast<TicTacToeMove*>(move);
    char moveValue = getXOrO(player_id);
    tttState->board[tttMove->getX()][tttMove->getY()] = moveValue;
    thisPlayerTurnOver = true;
}

std::vector<int> TicTacToe::scoreGameState(GameState& state) const
{ 
    
    if (getWinnerId() == WinnerId::Player1)
    {
        std::vector<int> scores{ 1, -1 };
        return scores;
    }
    else if (getWinnerId() == WinnerId::Player2)
    {
        std::vector<int> scores{ -1, 1 };
        return scores;
    }
    std::vector<int> scores{ 0, 0 };
    return scores;
}

bool isValidMove(GameState& state, Move& move) const
{
    
    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);
    return tttState->board[move.getX()][move.getY()] == '.';
}

// ToDo: should return bool
bool TicTacToe::isGameOver(GameState& state, WinnerId& winner) const
{
	

    TicTacToeState* tttState = dynamic_cast<TicTacToeState*>(state);

    for (int i = 0; i < 3; i++)
    {
        if (tttState->board[i][0] != '.' && tttState->board[i][0] == tttState->board[i][1] && tttState->board[i][0] == tttState->board[i][2])
        {
	    if (tttState->board[i][0] == 'X') {
		winner = WinnerId::Player1;
	    }else{
		winner = WinnerId::Player2;
	    }
            return true;
        }
        if (tttState->board[0][i] != '.' && tttState->board[0][i] == tttState->board[1][i] && tttState->board[0][i] == tttState->board[2][i])
        {
	    if (tttState->board[i][0] == 'X') {
		winner = WinnerId::Player1;
	    }else{
		winner = WinnerId::Player2;
	    }
            return true;
        }
    }

    for (int i = 0; i < 3; i += 2)
    {

        if (tttState->board[0][i] != '.' && tttState->board[0][i] == tttState->board[1][1] && tttState->board[0][i] == tttState->board[2][2 - i])
        {

	    if (tttState->board[i][0] == 'X') {
		winner = WinnerId::Player1;
	    }else{
		winner = WinnerId::Player2;
	    }
            return true;
        }
    }
    bool isOneBoxEmpty = false;
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    if (tttState->board[i][j] == '.') {
	        isOneBoxEmpty = true;
	    }
	}
    }
    if (isOneBoxEmpty == false) {
	winner = WinnerId::Tie;
	return true;
    }

    return false;
}

void makeMove(Move& move)
{
    simulateMove(state, move);
}

// ToDo: the game already knows who currPlayer is by currPlayerId
void TicTacToe::nextTurn()
{
     bool isTurnOver = false;
     while (!isTurnOver) {
         move = player.getMove(game.getState(), game.getmoves());
         game.simulateMove(state, move, currPlayerId, isTurnOver);
         currPlayerId = currPlayerId == PlayerId::Player1 ? PlayerId::Player2 : PlayerId::Player1;
     }
}

void TicTacToe::play()
{
    currPlayerId = PlayerId::Player1;
    WinnerId winner = WinnerId::None;
    while(!isGameOver(state, winner))
    {
      state.print();
      nextTurn();
    }

    state.print();

    if (winner == WinnerId::Player1)
    {
        cout << "Player 1 has won the game." << endl;
    }
    else if (winner == WinnerId::Player2)
    {
        cout << "Player 2 has won the game." << endl;
    }else  {
	cout << "The game ended in a tie." << endl;
    }
    // Check to see if each player is human or not, then run next turn
}
