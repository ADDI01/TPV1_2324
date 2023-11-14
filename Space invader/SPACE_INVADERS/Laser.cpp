#include "Laser.h"
#include "Game.h"

Laser:: Laser(Point2D<float> pos, Vector2D<float> velocity, uint father, Game* game, SDL_Renderer* myRenderer,
	uint w = 5, uint h = 10) :
	_pos(pos), _velocity(velocity), _father(father), _myGame(game), _myRenderer(myRenderer), _w(w), _h(h) {

	_myRect = new SDL_Rect;
	_myRenderer = new SDL_Renderer;
};

Laser:: ~Laser() {
	delete _myRect;
	_myRect = nullptr;
	delete _myRenderer;
	_myRenderer = nullptr;
};

void Laser::render() const {
	if (!_hit) 
	{
		_myRect->x = _pos.getX();
		_myRect->y = _pos.getY();
		_myRect->w = 5;
		_myRect->h = 10;
		SDL_SetRenderDrawColor(_myRenderer, 0, 0, 255, 0xFF);
		SDL_RenderFillRect(_myRenderer, _myRect);
	}
}

bool Laser::update() {
	//Checks if the laser has hit
	if (!_hit) 
	{
		if (_father == PLAYER) //Laser from player
		{
			_pos = _pos - _velocity; //Laser moves
		}
		else //Laser from alien
		{
			_pos = _pos + _velocity; //Laser moves
		}
	}

	return !_hit;
}

void Laser:: hit() {
	_hit = true;
}