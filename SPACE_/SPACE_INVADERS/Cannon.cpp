#include "Cannon.h"

Cannon:: ~Cannon() 
{
	delete _myTexture;
	_myTexture = nullptr;
	delete _myGame;
	_myGame = nullptr;
}

void Cannon::render() const
{

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