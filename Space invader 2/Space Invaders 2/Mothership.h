#pragma once
#include "GameObject.h"
#include "Vector2D.h"

using uint = unsigned int;

class Mothership: public GameObject
{
private:
	enum movementStates { RIGHT,DOWNLEFT, LEFT, DOWNRIGHT};
	movementStates _actualMovementState;
	Vector2D<float> _movementDirection;
	bool _canMove;
	int _level = 5;
	int _contAliens = 0;
	int _landedHeight = 0;
	
public:
	Mothership(Game* game) : GameObject(game), _actualMovementState(RIGHT) {};

	void render() const override {};
	bool update() override;
	bool save() const override { return true; };

	Vector2D<float> getDirection();
	bool shouldMove() { return _canMove; }
	void cannotMove() { _canMove = false; };
	void alienDied() { _contAliens--; };
	bool alienLanded(float y) { return y >= _landedHeight; };
	void haveLanded();
	uint getAlienCount() { return _contAliens; };
	void changeDirection();
	void addAlien() { _contAliens++; };
};