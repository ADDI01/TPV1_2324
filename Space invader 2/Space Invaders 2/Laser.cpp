#include "Laser.h"
#include "Game.h"
#include <fstream>

Laser::Laser(Point2D<float> pos, Vector2D<float> velocity, pair<uint, uint> size, Game* game, SDL_Renderer* myRenderer,
	Father father) : SceneObject(game, nullptr, pos, size, 1), _velocity(velocity), _father(father),
	_myRenderer(myRenderer) {
	_myRect = new SDL_Rect;
};

Laser:: ~Laser() {
	delete _myRect;
	_myRect = nullptr;
	_myRenderer = nullptr;
};

void Laser::render() const {
	if (_life > 0) {
		_myRect->x = _pos.getX();
		_myRect->y = _pos.getY();
		_myRect->w = _size.first;
		_myRect->h = _size.second;
		if(_father == ALIEN)
			SDL_SetRenderDrawColor(_myRenderer, 0, 0, 255, 0xFF);
		else if(_father == PLAYER)SDL_SetRenderDrawColor(_myRenderer, 255, 0, 0, 0xFF);
		SDL_RenderFillRect(_myRenderer, _myRect);
	}
}

void Laser::update() {
	
	if (_father == PLAYER) //Laser from player
	{
		_pos = _pos - _velocity; //Laser moves
	}
	else //Laser from alien
	{
		_pos = _pos + _velocity; //Laser moves
	}

	if (_pos.getY()<= 0 || _pos.getY() >= WIN_HEIGHT || _game->damage(*_myRect, _father)) {
		_game->hasDie(_it);
	}
}

bool Laser::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (typeOfDamage != _father && SDL_HasIntersection(&AttackRect, _myRect))
	{
			return true; // no poner el hash die, se llamaría 2 veces
	} 
	return false;
}

void Laser::save(std::ostream& out) const{
	out << 6 << " " << _pos.getX() << " " << _pos.getY() << " " << _father << endl;
}