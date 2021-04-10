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
    GameType
};

template <typename E>
auto as_integer(E const value)
    -> typename std::underlying_type<E>::type
{
    return static_cast<typename std::underlying_type<E>::type>(value);
}

class Minimax : public Engine
{
  protected:
    int depth; // ToDo: make -1 correspond to infinite depth (until game over)
    int nWorkers;
    std::shared_ptr<Move> min(const Game* game, GameState* state, int& scoreDiff, std::uint16_t depth);
    std::shared_ptr<Move> max(const Game* game, GameState* state, int& scoreDiff, std::uint16_t depth);
    mpi::environment mpiEnv;
    mpi::communicator childComm;

    void spawnWorkers();

  public:
    Minimax() :
        depth(5), nWorkers(0)
    {
        spawnWorkers();
    }

    Minimax(int depth, int nWorkers) :
        depth(depth), nWorkers(nWorkers)
    {
        spawnWorkers();
    }

    void setDepth(int depth) { this->depth = depth; }
    void setNProcesses(int nWorkers) { this->nWorkers = nWorkers; }
    std::shared_ptr<Move> getBestMove(const Game* game, GameState* state, GameType gameType, PlayerId playerId, int& score);
};