#include "ShooterAlien.h"
#include "Game.h"

bool ShooterAlien:: update() {
	Alien::update(); 

	if (_shootCD <= 0) //Shooter alien shoot
	{
		_shootCD = _game->getRandomRange(MIN_CD, MAX_CD);
		fireLaser();
		return true;
	}
	else
	{
		_shootCD--;
	}
}

void ShooterAlien::fireLaser() {
	Laser* l = new Laser(_pos - Vector2D<float>(0, _size.first / 2), Vector2D<float>(0, 10),
		pair<uint, uint>(5, 10), _game, _game->getRenderer(), ALIEN);
	_game->addToList(l);
}