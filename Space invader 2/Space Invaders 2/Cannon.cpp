#include "Cannon.h"
#include "Game.h"

Cannon:: ~Cannon() {
	_texture = nullptr;
	_game = nullptr;
	delete _myRect;
	_myRect = nullptr;
};

void Cannon::render() const
{
	_myRect->x = _pos.getX() - (_size.first / 2);
	_myRect->y = _pos.getY();
	_myRect->w = _size.first;
	_myRect->h = _size.second;

	_texture->render(*_myRect);
}

bool Cannon::update() {

	//Cannon tries to move out of the lateral limits
	if (!(_pos.getX() <= 0 + _size.first && _direction.getX() <= 0)
		&& !(_pos.getX() >= _game->getWidth() - _size.first && _direction.getX() >= 0))
	{
		_pos = _pos + _direction;
	}
	//Shoot on cooldown
	if (_shootCD >= 0)
	{
		_shootCD--;
	}
	return _life > 0;
}

void Cannon::handleEvents(const SDL_Event & event, SDL_Renderer* renderer) {
	switch (event.type)
	{
	case SDL_KEYDOWN:
		//Movement
		if (event.key.keysym.sym == SDLK_LEFT) 
			_direction = Vector2D<float>(-1, 0) * _velocity;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			_direction = Vector2D<float>(1, 0) * _velocity;
		//Shoot
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			if (canShoot())
			{
				fireLaser(renderer);
				setCoolDown(_iniShootCD);
			}
		} 
		break;

	case SDL_KEYUP:
		//Stop movement
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
		{
			_direction = Vector2D<float>(0, 0);
		}
		break;
	}
}

void Cannon::fireLaser(SDL_Renderer* renderer) {
	Laser* l = new Laser(_pos - Vector2D<float>(0, _size.first / 2), Vector2D<float>(0, 10), 
		pair<uint, uint>(5, 10), _game, renderer, PLAYER);
	_game->addToList(l);
}

bool Cannon::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (SDL_HasIntersection(&AttackRect, _myRect)) {
		_life--;
		std::cout << _life;
		if (_life == 0) {
			_game->lose();
		}
		return true;
	}
	return false;
}

bool Cannon::canShoot() const {
	return _shootCD <= 0;
}