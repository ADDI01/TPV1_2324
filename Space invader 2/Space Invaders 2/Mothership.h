#pragma once
#include "GameObject.h"
#include "Vector2D.h"

using uint = unsigned int;

class Mothership: public GameObject
{
private:
	enum movementStates {RIGHT, LEFT, LEVEL};
	movementStates _actualMovementState;

public: 
	Mothership() : _actualMovementState(RIGHT) {};
	Vector2D<float> getDirection() const;
	bool shouldMove();
	bool cannotMove();
	bool alienDied();
	bool alienLanded();
	bool haveLanded();
	uint getAlienCount();
};