#ifndef CANNON_H_
#define CANNON_H_

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

using uint = unsigned int;

class Game;

class Cannon
{
private:
	//Cannon's direction
	Vector2D<float> _direction;
	//Cannon's position
	Point2D<float> _pos;
	//Cannon's lifes
	uint _nLifes;
	//Pointer to texture
	Texture* _texture;
	//Pointer to Game class
	Game* _myGame;
	//Cannon's size
	uint _w = 0, _h = 0;
	//Destination and size of the cannon
	SDL_Rect* _myRect = nullptr;
	//Cannon's speed
	float _velocity = 0;
	//Cannon's shoot cooldown
	float _shootCD = 0;

public: 
	Cannon(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, uint nLifes, float shootCD,
		float velocity);
	~Cannon();

	//Game states
	void render() const;
	bool update();
	void handleEvents(Vector2D<float> direction);

	//Specific actions
	void hit();
	bool canShoot() const;
	
	//Setters
	void setCoolDown(float coolDown) { _shootCD = coolDown; };

	//Getters
	Vector2D<float> getPosition() const { return _pos; };
	SDL_Rect* getRect() const { return _myRect; };
};

#endif