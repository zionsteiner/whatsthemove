#pragma once
#include <boost/serialization/access.hpp>

class GameState
{

  private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {}

  public:
    virtual ~GameState() {}
    virtual void print() const = 0;
};
