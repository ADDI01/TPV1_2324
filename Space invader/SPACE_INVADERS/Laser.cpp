#include "Laser.h"
#include "Game.h"

void Laser::render() const
{
	SDL_Rect* myRect = new SDL_Rect;
	myRect->x = _pos.getX();
	myRect->y = _pos.getY();
	myRect->w = 5;
	myRect->h = 10;
	SDL_SetRenderDrawColor(_myrenderer,0,0,255,0xFF);
	SDL_RenderFillRect(_myrenderer, myRect);
	delete myRect;
}

bool Laser::update() 
{
	//llamamos a la comprobación de colisión
	if (_fatherPlayer) 
	{
		//movimiento de la bala del jugador
		_pos = _pos - _velocity;
	}
	else 
	{
		//movimiento de la bala de los alienígenas
		_pos = _pos + _velocity;
	}

	return true;
}