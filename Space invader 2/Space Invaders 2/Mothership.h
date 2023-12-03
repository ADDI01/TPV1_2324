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
	float _level = 0;
	float _actualLevel = 0;
	bool _bajada = false;

	int _contAliens = 0;
	int _landedHeight = 0;
	
public:
	Mothership(Game* game, int estado, int level, float movementCD) : GameObject(game), _actualMovementState((movementStates)estado), _level(level), _actualLevel(movementCD) {};

	void render() const override {};
	void update() override;
	void save(std::ostream& out) const override;

	Vector2D<float> getDirection();
	bool shouldMove() { return _actualLevel <= 0; }
	void bajaColumna() { _bajada = true; };
	void alienDied() { _contAliens--; };
	bool alienLanded(float y);
	void haveLanded();
	uint getAlienCount() { return _contAliens; };
	void changeDirection();
	void addAlien() { _contAliens++; };
	void setState(int state) { _actualMovementState = (movementStates) state; };
	void setLevel(float level) { _level = level; };
	void setActualLevel(int actualLevel) { _actualLevel = actualLevel; }
};