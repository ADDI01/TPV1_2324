#include "InfoBar.h"
#include "Game.h"

void InfoBar::render() const {
	_myRect->x = _pos.getX();
	_myRect->y = _pos.getY();
	_myRect->w = _size.first;
	_myRect->h = _size.second;

	switch(_game.getCannonLifes())
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
		throw "Enemigo incorrecto.";
		break;
	}
}

void InfoBar::update() {

}

