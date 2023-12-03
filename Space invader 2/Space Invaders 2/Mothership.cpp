#include "Mothership.h"
#include "Game.h"
#include <fstream>

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
			_level -= 0.5;

		_bajada = false;
	}
}

void Mothership::update() 
{
	if (_contAliens == 0) {
		_game->Win();
	}

	if (_bajada) {
		changeDirection();
	}
	if (_actualLevel <= 0) {
		_actualLevel = _level;
	}
	else _actualLevel--;
}

void Mothership::save(std::ostream& out) const {
	out << 3 << " " << _actualMovementState << " " << _level << " " << _actualLevel << endl;
}