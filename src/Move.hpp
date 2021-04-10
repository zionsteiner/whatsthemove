#pragma once
// ToDo: should Move and GameState be inner classes of Game?
#include <boost/serialization/access.hpp>
#include <string>

class Move
{

  protected:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {}

  public:
    virtual ~Move() {}
    virtual std::string toString() const = 0;
};
