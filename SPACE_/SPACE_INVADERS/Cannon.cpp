#include "Cannon.h"

Cannon:: ~Cannon() 
{
	//delete _texture;
	//_texture = nullptr;
	//delete _myGame;
	//_myGame = nullptr;
}

void Cannon::render() const
{
	SDL_Rect destRect;
	destRect.x = _pos.getX() - (_w / 2);
	destRect.y = _pos.getY();
	destRect.w = _w;
	destRect.h = _h;

	_texture->render(destRect);
}

void Cannon::update() 
{
	
}

void Cannon::Hit() 
{
	_nLifes--;
}

void Cannon::HandleEvents() 
{

}