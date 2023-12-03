#include "InfoBar.h"
#include "Game.h"

void InfoBar::render() const {
	_cannonRect->x = _pos.getX();
	_cannonRect->y = _pos.getY();
	_cannonRect->w = _size.first;
	_cannonRect->h = _size.second;

	switch (_game->getCannonLifes()) {
	case 1:
		_texture->render(*_cannonRect);
		break;
	case 2:
		_texture->render(*_cannonRect);
		_cannonRect->x = _pos.getX() + _cannonRect->w + _offset;
		_texture->render(*_cannonRect);
		break;
	case 3:
		_texture->render(*_cannonRect);
		_cannonRect->x += _cannonRect->w + _offset;
		_texture->render(*_cannonRect);
		_cannonRect->x += _cannonRect->w + _offset;
		_texture->render(*_cannonRect);
		break;
	default:
		SDLError r("Numero de cannons incorrecto.");
		throw r.what();
	}

}

void InfoBar::setPoints(uint type) {
	switch (type)
	{
	case 0: //Shooter
		_points += 30;
		break;
	case 1: //Small
		_points += 20;
		break;
	case 2: //Big
		_points += 10;
	case 3: //UFO
		_points += 100;
		break;
	default:
		SDLError r("Enemigo incorrecto.");
		throw r.what();
		break;
	}
}
