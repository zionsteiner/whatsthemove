#include "EnginePlayer.hpp"

EnginePlayer::EnginePlayer(Engine* engine)
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
    return engine->getBestMove(game->getGameState().get(), game->getCurrPlayerId(), score);
}