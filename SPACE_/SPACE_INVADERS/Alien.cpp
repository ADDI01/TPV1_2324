#include "Alien.h"

Alien:: ~Alien() 
{
	delete _myTexture;
	_myTexture = nullptr;
	delete _myGame;
	_myGame = nullptr;
}

void Alien::render() const
{

}

bool Alien::update() 
{
	bool retorno = true;
	if (_subType == 0) 
	{
		retorno = false;
	}

	return retorno;
}

void Alien::Hit() 
{
	_subType = 0;
}