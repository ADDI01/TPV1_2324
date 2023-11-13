#include "Bunker.h"

void Bunker:: render() const
{
	_myRect->x = _pos.getX();
	_myRect->y = _pos.getY();
	_myRect->w = _w;
	_myRect->h = _h;

	if (_nLifes > 0) {
		switch (_nLifes) {
		case 4:
			_texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
			break;
		case 3:
			_texture->renderFrame(*_myRect, 0, 1, SDL_FLIP_NONE);
			break;
		case 2:
			_texture->renderFrame(*_myRect, 0, 2, SDL_FLIP_NONE);
			break;
		case 1:
			_texture->renderFrame(*_myRect, 0, 3, SDL_FLIP_NONE);
			break;
		case 0:
			break;
		default:
			// Agregado para manejar bunkers inesperados
			throw "Bunker no existente.";
			break;
		}
	}
}

bool Bunker::update() 
{
	return _nLifes>0;
}

void Bunker::hit() 
{
	_nLifes--;
	//actualizar la imagen
}