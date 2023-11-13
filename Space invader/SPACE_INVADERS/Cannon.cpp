#include "Cannon.h"

void Cannon::render() const
{
	_myRect->x = _pos.getX() - (_w / 2);
	_myRect->y = _pos.getY();
	_myRect->w = _w;
	_myRect->h = _h;

	_texture->render(*_myRect);
}

bool Cannon::update() 
{
	if (!(_pos.getX() <= 0 && _direction.getX() <=0 + _w) && !(_pos.getX() >= 800- _w && _direction.getX() >= 0))
	{
			_pos = _pos + _direction;
	}
	if (_shootCD >= 0)
	{
		_shootCD--;
	}
	return _nLifes > 0;
}

bool Cannon::canShoot() const
{
	return _shootCD <= 0;
}

void Cannon::Hit() 
{
	_nLifes--;
	std::cout << _nLifes;
}

void Cannon :: handleEvents(Vector2D<float> direction) 
{
	_direction = direction * _velocity;
}