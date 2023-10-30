#include "Laser.h"
#include "Game.h"

void Laser::render() const
{
	/*SDL_Rect* myRect;
	myRect->x = 0;
	myRect->y = 0;
	myRect->w = 5;
	myRect->h = 10;
	SDL_RenderFillRect(_myrenderer, myRect);*/
}

bool Laser::update() 
{
	//llamamos a la comprobación de colisión
	if (_fatherPlayer) 
	{
		_pos = _pos - _velocity;
	}

	return true;
}