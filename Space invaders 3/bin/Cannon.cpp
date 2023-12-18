#include "Cannon.h"
#include "PlayState.h"
#include <fstream>

using namespace std;

Cannon::Cannon(Point2D<float> pos, Texture* texture, pair<uint, uint> size, GameState* State, PlayState* myPlayState, SDLApplication* app,
	uint nLifes, float shootCD,
	float velocity): SceneObject(State, myPlayState,app, texture, pos, size, nLifes), _shootCD(shootCD), _velocity(velocity),
	_myRect(SDL_Rect()) {};

Cannon::Cannon(GameState* gameState, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture, float velocity)
	: SceneObject(gameState, myPlayState,app, in, texture), _velocity(velocity)
{
	in >> _shootCD;
	//game->setLandedHeight(_pos.getY());
};

Cannon:: ~Cannon() {
	_texture = nullptr;
	_game = nullptr;
};

void Cannon::render() const
{
	_texture->render(_myRect);
}
void Cannon::update() 
{
	if (!(_pos.getX() <= 0 + _size.first && _direction.getX() <= 0) //Cannon tries to move out of the lateral limits
		&& !(_pos.getX() >= _myApp->getWidth() - _size.first && _direction.getX() >= 0))
	{
		_pos = _pos + _direction;
	}
	if (_shootCD >= 0) //Shoot on cooldown
	{
		_shootCD--;
	}

	//Cannon's Dest_Rect is modified
	_myRect.x = _pos.getX() - (_size.first / 2);
	_myRect.y = _pos.getY();
	_myRect.w = _size.first;
	_myRect.h = _size.second;
}

void Cannon::manageEvent(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_LEFT) //Movement
			_direction = Vector2D<float>(-0.1, 0) * _velocity;
		else if (event.key.keysym.sym == SDLK_RIGHT) //Movement
			_direction = Vector2D<float>(0.1, 0) * _velocity;
		else
			_direction = Vector2D<float>(0, 0);
		if (event.key.keysym.sym == SDLK_SPACE) //Shoot
		{
			if (canShoot())
			{
				fireLaser(_myApp->getRenderer());
				setCoolDown(_iniShootCD);
			}
		}
		break;
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) //Stop movement
		{
			_direction = Vector2D<float>(0, 0);
		}
		break;
	}
}


void Cannon::save(std::ostream & out) const {
	//out << 0 << " " << _pos.getX() << " " << _pos.getY() << " " << _life << " " << _shootCD << endl;
}
bool Cannon::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (typeOfDamage != PLAYER && SDL_HasIntersection(&AttackRect, &_myRect)) { //Alien bullet collides the cannon
		_life--;
		_pos = Vector2D<float>(WIN_WIDTH / 2, _pos.getY());
		std::cout << _life;
		if (_life == 0) { //No lifes left -> End the game
			//mygame->lose();
		}
		return true;
	}
	return false;
}

void Cannon::fireLaser(SDL_Renderer* renderer) {
	Laser* l = new Laser(_pos - Vector2D<float>(0, _size.second), Vector2D<float>(0, 5),
		pair<uint, uint>(5, 20), _game, _myPlayState, _myApp, renderer, PLAYER);
	_game->addObject(l);
	_myPlayState->addSceneObject(l);
}

bool Cannon::canShoot() const {
	return _shootCD <= 0;
}