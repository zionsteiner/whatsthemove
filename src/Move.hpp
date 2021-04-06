#pragma once
// ToDo: should Move and GameState be inner classes of Game?

class Move
{

private:
    void serialize(Archive& ar, const unsigned int version) {}

public:
	virtual ~Move() {}
};
