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
    int score;
    return engine->getBestMove(game, game->getGameState().get(), gameType, game->getCurrPlayerId(), score);
}