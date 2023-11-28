#pragma once

#include "Vector2D.h"
#include "checkML.h"
#include "Texture.h"

class Game;

using uint = unsigned int;

enum Father { ALIEN, PLAYER };

class Laser
{
private:
	//Laser's direction
	static Vector2D<float> _dir;
	//Pointer to Game class
	Game* _myGame = nullptr;
	//Game's renderer
	SDL_Renderer* _myRenderer = nullptr;
	//Destination and size of the laser
	SDL_Rect* _myRect = nullptr;
	//velocidad de la bala
	Vector2D<float> _velocity;
	//Defines the father. 
	Father _father;

	

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