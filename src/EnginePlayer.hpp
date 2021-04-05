#include "Player.hpp"
#include "Engine.hpp"
#include <memory>

class EnginePlayer : public Player
{
    protected:
        std::shared_ptr<Engine> engine;
    public:
    EnginePlayer(Engine* engine);
    void setEngine(Engine* engine);
    std::shared_ptr<Move> getMove(Game* game);
};