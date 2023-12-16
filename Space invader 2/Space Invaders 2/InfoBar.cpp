#include "InfoBar.h"
#include "Game.h"

using namespace std;

InfoBar::InfoBar(Game* game, Texture* texture, Point2D<float> pos, pair<uint, uint> size, uint points) : GameObject(game),
	_texture(texture), _points(points), _pos(pos), _size(size), _cannonLife1(SDL_Rect()), _cannonLife2(SDL_Rect()),
	_cannonLife3(SDL_Rect()), _pointsRect(SDL_Rect()) {}; //TODO: Pasar Rects de las vidas en el constructor por param


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
