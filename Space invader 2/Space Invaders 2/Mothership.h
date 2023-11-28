#pragma once
#include "GameObject.h"
#include "Vector2D.h"

using uint = unsigned int;

class Mothership: public GameObject
{
private:
	enum movementStates { RIGHT,LEFT};
	movementStates _actualMovementState;
	Vector2D<float> _movementDirection;
	bool _canMove = true;
	int _level = 5;
	int _contAliens = 0;
	int _landedHeight;
	
public:
	Mothership(Game* game) : GameObject(game), _actualMovementState(RIGHT) {};

	void render() const override {};
	bool update() override { return false; };
	bool save() const override { return true; };

	Vector2D<float> getDirection();
	bool shouldMove() { return _canMove; }
	void cannotMove() { _canMove = false; };
	void canMove() { _canMove = true; };
	void alienDied() { _contAliens--; };
	bool alienLanded(float y) { return y >= _landedHeight; };
	void haveLanded();
	uint getAlienCount() { return _contAliens; };
	void changeDirection();
	void addAlien() { _contAliens++; };
};