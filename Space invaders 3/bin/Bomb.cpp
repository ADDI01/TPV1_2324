#include "Bomb.h"
#include "PlayState.h"

Bomb::Bomb(GameState* game, PlayState* myPlayState, SDLApplication* app, SDL_Renderer* renderer, Texture* texture,
	Point2D<float> pos, std::pair<uint, uint> size, Vector2D<float> velocity, Father father) :
	SceneObject(game, myPlayState, app, texture, pos, size, 2), _velocity(velocity), _father(father), _myRect(SDL_Rect()) {};

void Bomb::render() const
{
	_texture->render(_myRect);
}

void Bomb::update()
{
	//Logica de choque con otro objeto
	_pos = _pos + _velocity;

	_myRect.x = _pos.getX();
	_myRect.y = _pos.getY();
	_myRect.w = _size.first;
	_myRect.h = _size.second;

	if (_myPlayState->damage(_myRect, _father)) {
		_life--;
	}
	if(_life == 0)
		_myPlayState->HasDied(_itS);
}

void Bomb::bombBehaviour(CallBack cB)
{
	cB();
}

bool Bomb::hit(SDL_Rect AttackRect, int typeOfDamage)
{
	return false;
};





