#include "Alien.h"
#include "Mothership.h"
#include "Game.h"

Alien::Alien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, Mothership* mother,
	float velocity, int type, bool idle): SceneObject(game,texture, pos, size, 1), _mother(mother), _velocity(velocity),
	_subType(type), _idle(idle){ 
	_myRect = new SDL_Rect;
	//_shootCD = _myGame->getRandomRange(MIN_CD, INT_CD); TODO: CLASE GAME
};

Alien:: ~Alien() {
	_texture = nullptr;
	_myGame = nullptr;
	_mother = nullptr;
	delete _myRect; //TODO: CAMBIAR ESTO
	_myRect = nullptr; //TODO: CAMBIAR ESTO
};

void Alien::render() const {
	_myRect->x = _pos.getX();
	_myRect->y = _pos.getY();
	_myRect->w = _size.first;
	_myRect->h = _size.second;

	//The alien is rendered depending on the subtype. 0 for shooters, 1 for greens, 2 for reds
	//Idle defines which frame is rendered. False for 1st frame, True for 2nd
	switch (_subType) {
	case 0:
		if (!_idle) _texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(*_myRect, 0, 1, SDL_FLIP_NONE);
		break;
	case 1:
		if (!_idle) _texture->renderFrame(*_myRect, 1, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(*_myRect, 1, 1, SDL_FLIP_NONE);
		break;
	case 2:
		if (!_idle) _texture->renderFrame(*_myRect, 2, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(*_myRect, 2, 1, SDL_FLIP_NONE);
		break;
	default:
		//When non expected alien comes
		throw "The Alien does not exist.";
		break;
	}
}

bool Alien:: update()
{
bool ret = true;
	if (_subType == -1) //The alien's dead
	{
		ret = false;
	}
	else
	{
		_pos = _pos + _mother->getDirection();
		_idle = !_idle;
		if ((_pos.getX() >= _game->getWidth() - _size.first && _mother->getDirection().getX() >= 0)|| (_pos.getX() <= 0 && _mother->getDirection().getX() <= 0))
		{
			_mother->cannotMove();
		}

		_mother->alienLanded(_pos.getY());
	}
	return ret;
}


bool Alien::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (SDL_HasIntersection(&AttackRect, _myRect)) 
	{
		_subType = -1;
		return true;
	}
	else 
	{
		return false;
	}
}

void Alien::bajaColumna() {
	_pos = _pos + Vector2D<float>(0, _size.second);
}