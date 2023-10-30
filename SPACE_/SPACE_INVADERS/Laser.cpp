#include "Laser.h"
#include "Game.h"

void Laser::render() const
{
	SDL_Rect target;
	_texture->render(target);
}

bool Laser::update() 
{

}