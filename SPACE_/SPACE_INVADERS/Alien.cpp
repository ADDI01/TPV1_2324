#include "Alien.h"

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

	// En función del parámetro subtipo, pintamos un alien u otro
	// 0 = disparador, 1 = verde y 2 = rojo
	switch (_subType) {
	case 0:
		_texture->renderFrame(destRect, 0, 0, SDL_FLIP_NONE);
		break;
	case 1:
		_texture->renderFrame(destRect, 1, 0, SDL_FLIP_NONE);
		break;
	case 2:
		_texture->renderFrame(destRect, 2, 0, SDL_FLIP_NONE);
		break;
	default:
		// Agregado para manejar aliens inesperados
		throw "Alien no existente.";
		break;
	}
}

bool Alien::update() 
{
	bool retorno = true;
	if (_subType == -1) 
	{
		retorno = false;
	}

	return retorno;
}

void Alien::Hit() 
{
	_subType = -1;
}