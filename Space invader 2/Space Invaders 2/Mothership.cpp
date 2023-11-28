#include "Mothership.h"
#include "Game.h"

Vector2D<float> Mothership::getDirection()
{
	if (shouldMove()) {
		switch (_actualMovementState)
		{
		case Mothership::RIGHT:
			_movementDirection = Vector2D<float>(1, 0);
			break;
		case Mothership::LEFT:
			_movementDirection = Vector2D<float>(-1, 0);
			break;
		default:
			break;
		}
	}
	else {
		_movementDirection = Vector2D<float>(0, 0);
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
		_actualMovementState = LEFT;
		break;
	case Mothership::LEFT:
		_actualMovementState = RIGHT;
		break;
	}
	_canMove = true;
}
