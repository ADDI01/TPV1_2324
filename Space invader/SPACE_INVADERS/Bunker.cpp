#include "Bunker.h"

void Bunker:: render() const
{
	SDL_Rect destRect;
	destRect.x = _pos.getX();
	destRect.y = _pos.getY();
	destRect.w = _w;
	destRect.h = _h;

	switch (_nLifes) {
	case 4:
		_texture->renderFrame(destRect, 0, 0, SDL_FLIP_NONE);
		break;
	case 3:
		_texture->renderFrame(destRect, 0, 1, SDL_FLIP_NONE);
		break;
	case 2:
		_texture->renderFrame(destRect, 0, 2, SDL_FLIP_NONE);
		break;
	case 1:
		_texture->renderFrame(destRect, 0, 3, SDL_FLIP_NONE);
		break;
	default:
		// Agregado para manejar bunkers inesperados
		throw "Bunker no existente.";
		break;
	}
}

bool Bunker::update() 
{
	bool retorno = true;
	if (_nLifes == 0)
	{
		this->~Bunker();
		retorno = false;
	}
		return retorno;
}

void Bunker::hit() 
{
	_nLifes--;
	//actualizar la imagen
}