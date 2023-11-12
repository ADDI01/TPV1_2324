#include "Alien.h"
#include "Game.h"

Alien:: ~Alien() 
{
	//delete _myTexture;
	//_myTexture = nullptr;
	//delete _myGame;
	//_myGame = nullptr;
}

void Alien::render() const
{
	SDL_Rect destRect;
	destRect.x = _pos.getX();
	destRect.y = _pos.getY();
	destRect.w = _w;
	destRect.h = _h;

	// En funci�n del par�metro subtipo, pintamos un alien u otro
	// 0 = disparador, 1 = verde y 2 = rojo
	switch (_subType) {
	case 0:
		if(!_idle) _texture->renderFrame(destRect, 0, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(destRect, 0, 1, SDL_FLIP_NONE);
		break;
	case 1:
		if (!_idle) _texture->renderFrame(destRect, 1, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(destRect, 1, 1, SDL_FLIP_NONE);
		break;
	case 2:
		if (!_idle) _texture->renderFrame(destRect, 2, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(destRect, 2, 1, SDL_FLIP_NONE);
		break;
	default:
		// Agregado para manejar aliens inesperados
		throw "Alien no existente.";
		break;
	}
}

void Alien::bajaColumna() 
{
	_pos = _pos + Vector2D<float>(0, _h);
}

bool Alien::update() 
{
	bool retorno = true;
	if (_subType == -1) 
	{
		retorno = false;
	}

	_pos = _pos + (_myGame->getDirection() * _velocity);

	if (_pos.getX() >= 800 - _w|| _pos.getX() <= 0) 
	{
		_myGame->cannotMove();
	}

	_idle = !_idle;
	return retorno;
}


void Alien::Hit() 
{
	_subType = -1;
}