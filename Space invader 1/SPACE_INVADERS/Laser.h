#ifndef LASER_H_
#define LASER_H_

#include "Vector2D.h"
#include "checkML.h"
#include "Texture.h"

class Game;

using uint = unsigned int;

class Laser
{
private:
	//Laser's direction
	static Vector2D<float> _dir;
	//Laser's position
	Point2D<float> _pos;
	//Collision's boolean
	bool _hit = false;
	//Pointer to Game class
	Game* _myGame = nullptr;
	//Laser's size
	uint _w = 0, _h = 0;
	//Game's renderer
	SDL_Renderer* _myRenderer = nullptr;
	//Destination and size of the laser
	SDL_Rect* _myRect = nullptr;
	//velocidad de la bala
	Vector2D<float> _velocity;
	//Defines the father. 
	uint _father;

	enum Father { ALIEN, PLAYER };

public:
	Laser(Point2D<float> pos, Vector2D<float> velocity, uint father, Game* game, SDL_Renderer* myRenderer,
		uint w, uint h);
	~Laser();

	//Game states
	void render() const;
	bool update();

	//Specific actions
	void hit();

	//Getters
	bool getFather() const { return _father; };
	SDL_Rect* getRect() const { return _myRect; };
};

#endif