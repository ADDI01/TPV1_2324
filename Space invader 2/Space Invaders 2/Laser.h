#pragma once
#pragma once
#include "Vector2D.h"
#include "checkML.h"
#include "SceneObject.h"
#include "Texture.h"

class Game;

using uint = unsigned int;

enum Father { ALIEN, PLAYER };

class Laser : public SceneObject
{
private:
	//Laser's direction
	static Vector2D<float> _dir;
	//Game's renderer
	SDL_Renderer* _myRenderer = nullptr;
	//Destination and size of the laser
	SDL_Rect* _myRect = nullptr;
	//velocidad de la bala
	Vector2D<float> _velocity;
	//Defines the father. 
	Father _father;

public:
	Laser(Point2D<float> pos, Vector2D<float> velocity, pair<uint, uint> size, Game* game, SDL_Renderer* myRenderer,
		Father father);
	~Laser();

	//Game states
	void render() const override;
	bool update() override;
	bool save() const override { return true; };

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;

	//Getters
	bool getFather() const { return _father; };
	SDL_Rect* getRect() const { return _myRect; };
};