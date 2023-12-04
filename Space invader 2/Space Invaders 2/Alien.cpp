#include "Alien.h"
#include "Game.h"

Alien::Alien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game,
	float velocity, int type, bool idle): SceneObject(game,texture, pos, size, 1), _velocity(velocity), 
	_subType(type), _idle(idle){ 
	_myRect = new SDL_Rect;
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
		throw SDLError("The Alien does not exist.");
		break;
	}
}

void Alien:: update()
{
	if (_mother->shouldMove()) {
		_pos = _pos + _mother->getDirection();
		_idle = !_idle;
		if ((_pos.getX() >= _game->getWidth() - _size.first && _mother->getDirection().getX() >= 0) || (_pos.getX() <= 0 && _mother->getDirection().getX() <= 0))
		{
			_mother->bajaColumna();
		}
	}

	if (_mother->alienLanded(_pos.getY())) {
		_mother->haveLanded();
	}
}


bool Alien::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (typeOfDamage != 0 && SDL_HasIntersection(&AttackRect, _myRect)) 
	{
		if (_subType != -1) {
			_subType = -1;
			_game->hasDie(_it);
			_mother->alienDied();
		}
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

void Alien::save(std::ostream& out) const {

	out << 1 << " " << _pos.getX() << " " << _pos.getY() << " " << _subType << endl;
}