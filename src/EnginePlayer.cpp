#include "EnginePlayer.hpp"

EnginePlayer::EnginePlayer(Engine* engine)
{
    setEngine(engine);
}

void EnginePlayer::setEngine(Engine* engine)
{
    this->engine = std::shared_ptr<Engine>(engine);
}

std::shared_ptr<Move> EnginePlayer::getMove(Game* game)
{
    int depth = 3;
    int nProcesses = 3;

    return engine->getBestMove(game, game->getGameState().get(), game->getCurrPlayerId(), nProcesses);
}