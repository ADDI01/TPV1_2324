#include "Mothership.h"
#include "Game.h"

Vector2D<float> Mothership::getDirection()
{
	switch (_actualMovementState)
	{
	case Mothership::RIGHT:
		_movementDirection = Vector2D<float>(1, 0);
		break;
	case Mothership::LEFT:
		_movementDirection = Vector2D<float>(-1, 0);
		break;
	case Mothership:: DOWNLEFT && Mothership::DOWNRIGHT:
		_movementDirection = Vector2D<float>(0, 1);
		break;
	default:
		break;
	}
	
	return _movementDirection * _level;
}

void Mothership::haveLanded() 
{
	_game->lose();
}

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
}

bool Mothership::update() 
{
	if (!shouldMove())
	{
		_canMove = true;
		changeDirection();
	}
	return true;
}
