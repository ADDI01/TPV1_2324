#include "Laser.h"
#include "Game.h"

void Laser::render() const
{
	SDL_Rect* myRect;
	myRect->x = 0;
	myRect->y = 0;
	myRect->w = 5;
	myRect->h = 10;
	SDL_RenderFillRect(_myrenderer, myRect);
}

bool Laser::update() 
{
	//llamamos a la comprobaci�n de colisi�n
	if (_fatherPlayer) 
	{
		//movimiento de la bala del jugador
		_pos = _pos - _velocity;
	}
	else 
	{
		//movimiento de la bala de los alien�genas
		_pos = _pos + _velocity;
	}

	return true;
}