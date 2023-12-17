#include "InfoBar.h"
#include "Game.h"

using namespace std;

InfoBar::InfoBar(Game* game, Texture* texture, Point2D<float> pos, pair<uint, uint> size, uint points) : GameObject(game),
	_texture(texture), _points(points), _pos(pos), _size(size)
{
	_cannonLife1.w = _cannonLife2.w = _cannonLife3.w = texture->getFrameWidth();
	_cannonLife1.h = _cannonLife2.h = _cannonLife3.h = texture->getFrameHeight();
	_cannonLife1.y = _cannonLife2.y = _cannonLife3.y = WIN_HEIGHT - texture->getFrameHeight() - _offset;
	_cannonLife1.x = _offset; 
	_cannonLife2.x = texture->getFrameWidth() + _offset * 2;
	_cannonLife3.x = texture->getFrameWidth() * 2 + _offset * 3;

	//_pointsRect(SDL_Rect())
}; //TODO: Pasar Rects de las vidas en el constructor por param


InfoBar::~InfoBar() {
	_texture = nullptr;
};

void InfoBar::render() const {
	switch (_game->getCannonLifes()) { //Renders the current number of cannon's lifes
	case 0:
		break;
	case 1:
		_texture->render(_cannonLife1);
		break;
	case 2:
		_texture->render(_cannonLife1);
		_texture->render(_cannonLife2);
		break;
	case 3:
		_texture->render(_cannonLife1);
		_texture->render(_cannonLife2);
		_texture->render(_cannonLife3);
		break;
	default:
		throw SDLError("Numero de cannons incorrecto.");
	}

	//Renders the current puntuation (TODO)

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
