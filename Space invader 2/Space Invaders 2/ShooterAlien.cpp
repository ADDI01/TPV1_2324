#include "ShooterAlien.h"
#include "Game.h"

bool ShooterAlien:: update() {
	Alien::update(); 

	if (_shootCD <= 0) //Shooter alien shoot
	{
		_shootCD = _game->getRandomRange(MIN_CD, MAX_CD);
		_game->fireLaser(this);
		return true;
	}
	else
	{
		_shootCD--;
	}

}