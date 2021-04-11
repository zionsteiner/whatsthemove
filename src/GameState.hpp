#pragma once
#include <boost/serialization/access.hpp>
#include <memory>

class GameState
{

  private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {}

  public:
    virtual ~GameState() {}
    virtual void print() const = 0;
    virtual std::shared_ptr<GameState> clone() const = 0;
};
