#pragma once
#include "GameObject.h"
#include "Vector2D.h"

using uint = unsigned int;

class Mothership: public GameObject
{
private:
	enum movementStates {RIGHT,DOWNR, LEFT, DOWNL}; // downl & downr indican de qué dirección vienes
	movementStates _actualMovementState;
	int level;
	
public: 
	Mothership(Game* game) : GameObject(game), _actualMovementState(RIGHT) {};
	Vector2D<float> getDirection() const;
	bool shouldMove() {}
	bool cannotMove();
	bool alienDied();
	bool alienLanded();
	bool haveLanded();
	uint getAlienCount();
};