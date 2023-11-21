#include "Bunker.h"

Bunker:: Bunker(Point2D<float> pos, Texture* texture, uint w, uint h, uint nLifes)
	: _pos(pos), _texture(texture), _w(w), _h(h), _nLifes(nLifes) {

	_myRect = new SDL_Rect;
};

Bunker:: ~Bunker() { 
	delete _myRect; 
	_myRect = nullptr; 
	_texture = nullptr; 
};

void Bunker:: render() const {
	_myRect->x = _pos.getX();
	_myRect->y = _pos.getY();
	_myRect->w = _w;
	_myRect->h = _h;

	//The frame of the bunker is rendered depending on the current lifes
	if (_nLifes > 0) {
		switch (_nLifes) {
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
			throw "The Bunker does not exist.";
			break;
		}
	}
}

bool Bunker::update() {
	return _nLifes > 0;
}

void Bunker::hit() {
	_nLifes--;
}