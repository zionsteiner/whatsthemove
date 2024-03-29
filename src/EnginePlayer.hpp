#include "Engine.hpp"
#include "Player.hpp"

#include <memory>

class EnginePlayer : public Player
{
  protected:
    std::shared_ptr<Engine> engine;
    GameType gameType;

  public:
    EnginePlayer(Engine* engine);
    void setEngine(Engine* engine);
    std::shared_ptr<Move> getMove(const Game* game, std::vector<std::shared_ptr<Move>> moves);
};