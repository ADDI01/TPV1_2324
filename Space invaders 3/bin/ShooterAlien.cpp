#include "ShooterAlien.h"
#include "Laser.h"
#include <fstream>
#include "PlayState.h"

using namespace std;

ShooterAlien:: ShooterAlien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, GameState* game, PlayState* myPlayState, SDLApplication* app,
	float velocity, int type, bool idle) : Alien(pos, texture, size, game, myPlayState, app, velocity, type, idle)
{
	_shootCD = _myPlayState->getRandomRange(MIN_CD, MAX_CD);
};

ShooterAlien::ShooterAlien(GameState* game, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture, uint velocity, int lastestRow) :
	Alien(game, myPlayState, app, in, texture, velocity, lastestRow)
{
	in >> _shootCD;
};

void ShooterAlien:: update() {
	Alien::update(); 

	if (_shootCD <= 0) //Shooter alien shoot
	{
		_shootCD = _myPlayState->getRandomRange(MIN_CD, MAX_CD);
		fireLaser();
	}
	else
	{
		_shootCD--;
	}
}

void ShooterAlien::fireLaser() {
	/*Laser* l = new Laser(_pos + Vector2D<float>(_size.first / 2, _size.second), _game->getLaser_Speed(),
		_game->getLaser_Size(), _game, _game->getRenderer(), ALIEN);
	_game->addToList(l);  */          
	Laser* l = new Laser(_pos + Vector2D<float>(_size.first / 2, _size.second),_myPlayState->getLaser_Speed(),
		_myPlayState->getLaser_Size(), _game,_myPlayState,_myApp, _myApp->getRenderer(), ALIEN);
	_game->addObject(l);
	_myPlayState->addSceneObject(l);
}

void ShooterAlien::save(std::ostream& out) const {
	out << 2 << " " << _pos.getX() << " " << _pos.getY() << " " << _subType << " " << _shootCD << endl;
}