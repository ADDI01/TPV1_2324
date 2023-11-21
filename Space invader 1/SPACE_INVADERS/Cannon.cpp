#include "Cannon.h"
#include "Game.h"

Cannon:: Cannon(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, uint nLifes, float shootCD,
	float velocity) : _pos(pos), _texture(texture), _w(w), _h(h), _myGame(game), _nLifes(nLifes), 
	_shootCD(shootCD), _velocity(velocity) {

	_myRect = new SDL_Rect;
};

Cannon:: ~Cannon() { 
	_texture = nullptr; 
	_myGame = nullptr; 
	delete _myRect; 
	_myRect = nullptr; 
};

void Cannon::render() const
{
	_myRect->x = _pos.getX() - (_w / 2);
	_myRect->y = _pos.getY();
	_myRect->w = _w;
	_myRect->h = _h;

	_texture->render(*_myRect);
}

bool Cannon::update() {

	//Cannon tries to move out of the lateral limits
	if (!(_pos.getX() <= 0 + _w && _direction.getX() <=0) 
		&& !(_pos.getX() >= _myGame->getWidth() - _w && _direction.getX() >= 0))
	{
			_pos = _pos + _direction;
	}
	//Shoot on cooldown
	if (_shootCD >= 0)
	{
		_shootCD--;
	}
	return _nLifes > 0;
}

void Cannon::handleEvents(Vector2D<float> direction) {
	_direction = direction * _velocity;
}

void Cannon::hit() {
	_nLifes--;
	std::cout << _nLifes;
}

bool Cannon::canShoot() const {
	return _shootCD <= 0;
}