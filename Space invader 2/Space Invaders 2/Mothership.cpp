#include "Mothership.h"
#include "Game.h"
#include <fstream>

using namespace std;

Mothership::Mothership(Game* game, int estado, int level, float movementCD) : GameObject(game), 
	_actualMovementState((movementStates)estado), _level(level), _currentLevel(movementCD) {};

void Mothership::update()
{
	if (_contAliens == 0) {
		_game->win();
	}

	if (_lower) {
		changeDirection();
	}
	if (_currentLevel <= 0) {
		_currentLevel = _level;
	}
	else _currentLevel--;
}

void Mothership::save(std::ostream& out) const {
	out << 3 << " " << _actualMovementState << " " << _level << " " << _currentLevel << endl;
}

Vector2D<float> Mothership::getDirection()
{
	switch (_actualMovementState)
	{
	case Mothership::RIGHT:
		_movementDirection = Vector2D<float>(4, 0);
		break;
	case Mothership::LEFT:
		_movementDirection = Vector2D<float>(-4, 0);
		break;
	case Mothership:: DOWNLEFT:
		_movementDirection = Vector2D<float>(0, 25);
		break;
	case Mothership::DOWNRIGHT:
		_movementDirection = Vector2D<float>(0, 25);
		break;
	default:
		break;
	}
	
	return _movementDirection;
}

void Mothership::haveLanded() 
{
	_game->lose();
}

bool Mothership:: alienLanded(float y) { return y >= _game->getLandedHeight(); }

void Mothership:: changeDirection() {
	switch (_actualMovementState)
	{
	case Mothership::RIGHT:
		_actualMovementState = DOWNLEFT;
		break;
	case Mothership::DOWNLEFT:
		_actualMovementState = LEFT;
		break;
	case Mothership::LEFT:
		_actualMovementState = DOWNRIGHT;
		break;
	case Mothership::DOWNRIGHT:
		_actualMovementState = RIGHT;
		break;
	}

	if (_actualMovementState != RIGHT || _actualMovementState != LEFT) {

		if(_level >= 0)
			_level--;

		_lower = false;
	}
}