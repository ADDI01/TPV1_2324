#include "Bunker.h"
#include "Game.h"
#include <fstream>

Bunker::Bunker(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, uint nLifes)
	: SceneObject(game, texture, pos, size, nLifes) {

	_myRect = new SDL_Rect;
};

Bunker:: ~Bunker() {
	delete _myRect;
	_myRect = nullptr;
};

void Bunker::render() const {
	_myRect->x = _pos.getX();
	_myRect->y = _pos.getY();
	_myRect->w = _size.first;
	_myRect->h = _size.second;

	//The frame of the bunker is rendered depending on the current lifes
	if (_life > 0) {
		switch (_life) {
		case 4:
			_texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
			break;
		case 3:
			_texture->renderFrame(*_myRect, 0, 1, SDL_FLIP_NONE);
			break;
		case 2:
			_texture->renderFrame(*_myRect, 0, 2, SDL_FLIP_NONE);
			break;
		case 1:
			_texture->renderFrame(*_myRect, 0, 3, SDL_FLIP_NONE);
			break;
		case 0:
			break;
		default:
			//When non expected bunker comes
			SDLError r("The Bunker does not exist.");
			throw r.what();
			break;
		}
	}
}

void Bunker::update() {
	if (_game->damage(*_myRect, BUNKER))
	{
		_life--;
		if (_life == 0) {
			_game->hasDie(_it);
		}
	}
}

bool Bunker::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (typeOfDamage != 2)
	{
		if (SDL_HasIntersection(&AttackRect, _myRect)) {
			return true;
		}
	}
	else
	{
		return false;
	}
}

void Bunker::save(std::ostream& out) const {
	out << 4 << " " << _pos.getX() << " " << _pos.getY() << " " << _life << endl;
}