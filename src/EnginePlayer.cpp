#include "EnginePlayer.hpp"

EnginePlayer::EnginePlayer(Engine* engine, GameType gameType) :
    gameType(gameType)
{
    setEngine(engine);
}

void EnginePlayer::setEngine(Engine* engine)
{
    this->engine = std::shared_ptr<Engine>(engine);
}

std::shared_ptr<Move> EnginePlayer::getMove(const Game* game, std::vector<std::shared_ptr<Move>> moves)
{
    int depth = 3;
    int nProcesses = 3;

    int score;
    return engine->getBestMove(game, game->getGameState(), gameType, game->getCurrPlayerId(), score);
}