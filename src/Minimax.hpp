#pragma once

#include "Engine.hpp"
#include "Game.hpp"
#include "GameState.hpp"

#include <boost/mpi.hpp>
#include <cstdint>
#include <memory>

namespace mpi = boost::mpi;

enum class MPITag
{
    BestMove,
    Moves,
    PlayerId,
    State,
    Score,
    Depth,
    GameType,
    Start,
    Exit
};

template <typename E>
auto as_integer(E const value)
    -> typename std::underlying_type<E>::type // Wtf?
{
    return static_cast<typename std::underlying_type<E>::type>(value);
}

// ToDo: test this logic on a more complicated game (scores besides win/lose).
class Minimax : public Engine
{
  protected:
    int depth;    // ToDo: make -1 correspond to infinite depth (until game over)
    int nWorkers; // ToDo: not sure if oversubscribe works for spawned processes, if not, not sure what the max should be
    std::shared_ptr<Move> min(GameState* state, int& scoreDiff, std::uint16_t depth);
    std::shared_ptr<Move> max(GameState* state, int& scoreDiff, std::uint16_t depth);
    mpi::environment mpiEnv;
    mpi::communicator childComm;

    void spawnWorkers();

  public:
    Minimax(GameType gameType) :
        Engine(gameType), depth(5), nWorkers(0)
    {
        spawnWorkers();
    }

    Minimax(GameType gameType, int depth, int nWorkers) :
        Engine(gameType), depth(depth), nWorkers(nWorkers)
    {
        spawnWorkers();
    }

    ~Minimax()
    {
        if (nWorkers > 0)
        {
            for (int i = 0; i < nWorkers; ++i)
            {
                childComm.send(i, as_integer(MPITag::Exit));
            }
        }
    }

    void setDepth(int depth) { this->depth = depth; }
    void setNProcesses(int nWorkers) { this->nWorkers = nWorkers; }
    std::shared_ptr<Move> getBestMove(GameState* state, PlayerId playerId, int& score);
};