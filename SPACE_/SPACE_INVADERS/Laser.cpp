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

}