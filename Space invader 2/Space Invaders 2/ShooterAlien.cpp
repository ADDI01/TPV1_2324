#include "ShooterAlien.h"

bool ShooterAlien:: update() {
	Alien::update(); 

	if (_shootCD <= 0) //Shooter alien shoot
	{
		_shootCD = _game->getRandomRange(MIN_CD, MAX_CD);
		_game->fireLaser(this); //Instanciate alien's laser	
	}
	else
	{
		_shootCD--;
	}

}