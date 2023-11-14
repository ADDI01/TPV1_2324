#include "Alien.h"
#include "Game.h"

Alien:: Alien(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, float velocity, uint type, bool idle)
	: _pos(pos), _texture(texture), _myGame(game), _velocity(velocity), _w(w), _h(h), _subType(type), _idle(idle) {

	_myRect = new SDL_Rect;
	_shootCD = _myGame->getRandomRange(MIN_CD, INT_CD);
}

Alien:: ~Alien() { 
	_texture = nullptr; 
	_myGame = nullptr; 
	delete _myRect; 
	_myRect = nullptr; 
};

void Alien::render() const {

	_myRect->x = _pos.getX();
	_myRect->y = _pos.getY();
	_myRect->w = _w;
	_myRect->h = _h;

	//The alien is rendered depending on the subtype. 0 for shooters, 1 for greens, 2 for reds
	//Idle defines which frame is rendered. False for 1st frame, True for 2nd
	switch (_subType) {
	case 0:
		if(!_idle) _texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
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
	case - 1:
		break;
	default:
		//When non expected alien comes
		throw "The Alien does not exist.";
		break;
	}
}

bool Alien::update() {

	bool ret = true;
	if (_subType == -1) //The alien's dead
	{
		ret = false;
	}

	else
	{
		_pos = _pos + (_myGame->getDirection() * _velocity); //Alien moves

		if (_pos.getX() >= _myGame->getWidth() - _w || _pos.getX() <= 0) //Alien tries to move out of lateral limits
		{
			_myGame->cannotMove();
		}

		if (_subType == 0 && _shootCD <= 0) //Shooter alien shoot
		{
			_shootCD = _myGame->getRandomRange(MIN_CD, MAX_CD);
			_myGame->fireLaser(this); //Instanciate alien's laser	
		}
		else
		{
			_shootCD--;
		}
		_idle = !_idle;
	}
	if (_pos.getY() >= _myGame->getHeight() + _h) //If aliens reach the bottom, the game ends
	{
		_myGame->lose();
	}

	return ret;
}

void Alien::hit() {
	_subType = -1;
}

void Alien::bajaColumna() {
	_pos = _pos + Vector2D<float>(0, _h);
}