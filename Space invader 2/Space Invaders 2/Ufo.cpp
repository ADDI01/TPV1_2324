#include "Ufo.h"


void Ufo::render() const
{
	_myRect->x = _pos.getX() - (_size.first / 2);
	_myRect->y = _pos.getY();
	_myRect->w = _size.first;
	_myRect->h = _size.second;

	switch (_actualState)
	{
	case Ufo::VISIBLE:
		_texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
		break;
	case Ufo::OCULTO:
		break;
	case Ufo::DESTRUIDO:
		_texture->renderFrame(*_myRect, 0, 1, SDL_FLIP_NONE);
		break;
	default:
		throw "no ufo";
		break;
	}
}
