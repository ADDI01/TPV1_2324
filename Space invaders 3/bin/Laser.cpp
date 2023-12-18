#include "Laser.h"
#include "PlayState.h"
#include <fstream>

using namespace std;

Laser::Laser(Point2D<float> pos, Vector2D<float> velocity, pair<uint, uint> size, GameState* game, PlayState* myPlayState, SDLApplication* app,
	SDL_Renderer* myRenderer,Father father) : SceneObject(game,myPlayState, app, nullptr, pos, size, 1), _velocity(velocity), _father(father),
	_myRenderer(myRenderer), _myRect(SDL_Rect()) {};

Laser::Laser(GameState* game, PlayState* myPlayState, SDLApplication* app, SDL_Renderer* renderer, std::ifstream& in, std::pair<uint, uint> size, Vector2D<float> velocity):
	SceneObject(game,myPlayState, app, in, _size, 1), _myRenderer(renderer), _velocity(velocity), _myRect(SDL_Rect())
{
	int father;

	in >> father;
	_father = (Father)father;
};

Laser:: ~Laser() {
	_myRenderer = nullptr;
};

void Laser::render() const {
	if(_father == ALIEN) //Laser from Alien
		SDL_SetRenderDrawColor(_myRenderer, 0, 0, 255, 0xFF);
	else if(_father == PLAYER) //Laser from Cannon
		SDL_SetRenderDrawColor(_myRenderer, 255, 0, 0, 0xFF); 
	SDL_RenderFillRect(_myRenderer, &_myRect);
}

void Laser::update() {

	//Laser's Dest_Rect is modified
	_myRect.x = _pos.getX();
	_myRect.y = _pos.getY();
	_myRect.w = _size.first;
	_myRect.h = _size.second;

	if (_life > 0) {
		if (_father == PLAYER) //Laser from player
		{
			_pos = _pos - _velocity; //Laser moves
		}
		else //Laser from alien
		{
			_pos = _pos + _velocity; //Laser moves
		}
		//Laser gets out of limits of screen or hits something
		if (_pos.getY() <= 0 || _pos.getY() >= WIN_HEIGHT || _myPlayState->damage(_myRect, _father)) { 
			_myPlayState->HasDied(_itS);
		}
	}
}

void Laser::save(std::ostream& out) const {
	out << 6 << " " << _pos.getX() << " " << _pos.getY() << " " << _father << endl;
}

bool Laser::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (typeOfDamage != _father && SDL_HasIntersection(&AttackRect, &_myRect))
	{
		_myPlayState->HasDied(_itS);
		return true; //No need to call hasDie()
	} 
	return false;
}