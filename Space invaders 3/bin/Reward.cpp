#include "Reward.h"
#include "PlayState.h"

Reward::Reward(GameState* game, PlayState* myPlayState, SDLApplication* app,
	SDL_Renderer* renderer, Texture* texture, Point2D<float>pos, std::pair<uint, uint> size, Vector2D<float> velocity, Father father) :
	SceneObject(game, myPlayState, app, texture, pos, size, 0), _myRect(SDL_Rect()), _velocity(velocity), _father(father) {}

void Reward::rewardBehaviour()
{
	_cB();
};

void Reward::render() const
{
	_texture->render(_myRect);
};

void Reward::update()
{
	//Logica de choque con otro objeto
	_pos = _pos + _velocity;

	_myRect.x = _pos.getX();
	_myRect.y = _pos.getY();
	_myRect.w = _size.first;
	_myRect.h = _size.second;
	if (_myPlayState->mayGrantReward(_myRect)) {
		rewardBehaviour();
		_myPlayState->HasDied(_itS);
	}
};

bool Reward::hit(SDL_Rect AttackRect, int typeOfDamage)
{
	return false;
};
