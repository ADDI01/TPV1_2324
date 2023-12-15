#include "ShooterAlien.h"
#include "Game.h"
#include <fstream>

using namespace std;

ShooterAlien:: ShooterAlien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, float velocity, int type, bool idle) : Alien(pos, texture, size, game, velocity, type, idle)
{
	_shootCD = _game->getRandomRange(MIN_CD, MAX_CD);
};

void ShooterAlien:: update() {
	Alien::update(); 

	if (_shootCD <= 0) //Shooter alien shoot
	{
		_shootCD = _game->getRandomRange(MIN_CD, MAX_CD);
		fireLaser();
	}
	else
	{
		_shootCD--;
	}
}

void ShooterAlien::fireLaser() {
	Laser* l = new Laser(_pos + Vector2D<float>(_size.first / 2, _size.second), Vector2D<float>(0, 5),
		pair<uint, uint>(5, 20), _game, _game->getRenderer(), ALIEN);
	_game->addToList(l);
}

void ShooterAlien::save(std::ostream& out) const {
	out << 2 << " " << _pos.getX() << " " << _pos.getY() << " " << _subType << " " << _shootCD << endl;
}