#pragma once

#include "GameObject.h"
#include "Vector2D.h"

using uint = unsigned int;

class Mothership: public GameObject
{
private:
	//Types of alien's move
	enum movementStates { RIGHT,DOWNLEFT, LEFT, DOWNRIGHT};
	//Current movement of the aliens
	movementStates _actualMovementState;
	//Current direction of the movement
	Vector2D<float> _movementDirection;
	//Related to the velocitity of the aliens
	float _level = 0;
	//Current level
	float _currentLevel = 0;
	//Inidicates when aliens have to lower a column
	bool _lower = false;
	//Number of aliens
	int _contAliens = 0;
	//Inidicates the exact height which leads to lose the game if aliens reach it
	int _landedHeight = 0;
	
public:
	Mothership(Game* game, int estado, int level, float movementCD);
	~Mothership() {};

	//Game states
	void render() const override {};
	void update() override;
	void save(std::ostream& out) const override;

	//Specifics actions
	bool shouldMove() const { return _currentLevel <= 0; }
	void lowerColumn() { _lower = true; };
	void alienDied() { _contAliens--; };
	bool alienLanded(float y) const;
	void haveLanded();
	void changeDirection();
	void addAlien() { _contAliens++; };

	//Setters
	void setState(int state) { _actualMovementState = (movementStates) state; };
	void setLevel(float level) { _level = level; };
	void setActualLevel(int actualLevel) { _currentLevel = actualLevel; }

	//Getters
	Vector2D<float> getDirection();
	uint getAlienCount() const { return _contAliens; };
};