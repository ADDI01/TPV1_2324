#pragma once
#include "GameObject.h"
#include "Vector2D.h"

using uint = unsigned int;

class Mothership: public GameObject
{
private:
	enum movementStates { RIGHT, DOWNR, LEFT, DOWNL }; // downl & downr indican de qué dirección vienes
	movementStates _actualMovementState;
	Vector2D<float> _movementDirection = Vector2D<float>(1,0);
	bool _canMove;
	int _level = 5;
	int _contAliens = 0;
	int _landedHeight;
	
public: 
	Mothership(Game* game) : GameObject(game), _actualMovementState(RIGHT) {};

	void render() const override {};
	bool update() override { return false; };
	bool save() override { return false; };

	Vector2D<float> getDirection() const { return _movementDirection * _level; };
	bool shouldMove() { return _canMove; }
	void cannotMove() { _canMove = false; };
	void alienDied() { _contAliens--; };
	bool alienLanded(float y) { return y > _landedHeight; };
	void haveLanded();
	uint getAlienCount() { return _contAliens; };
};