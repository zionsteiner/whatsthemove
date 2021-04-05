#pragma once

#include "Engine.hpp"
#include "GameState.hpp"
#include "Game.hpp"
#include <memory>

#include <cstdint>

enum MPITag
{
  BestMove,
  Moves,
  PlayerId,
  State,
  Score,
  Depth
};

class Minimax : public Engine
{
  protected:
    int depth;
    int nWorkers;
    std::shared_ptr<Move> min(Game* game, GameState* state, int& scoreDiff, PlayerId playerId, std::uint16_t depth);
    std::shared_ptr<Move> max(Game* game, GameState* state, int& scoreDiff, PlayerId playerId, std::uint16_t depth);
    mpi::environment mpiEnv;
    mpi::communicator childComm;

    void spawnWorkers();

public:
    Minimax(): depth(5), nWorkers(0) 
    {
      spawnWorkers();
    }

    Minimax(int depth, int nWorkers): depth(depth), nWorkers(nWorkers) 
    {
      spawnWorkers();
    }

    void setDepth(int depth) { this->depth = depth; }
    void setNProcesses(int nWorkers) { this->nWorkers = nWorkers; }
    std::shared_ptr<Move> getBestMove(Game* game, GameState* state, int playerId);
};