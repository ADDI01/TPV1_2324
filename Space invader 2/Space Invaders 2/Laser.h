#pragma once

#include "Vector2D.h"
#include "checkML.h"
#include "SceneObject.h"
#include "Texture.h"

class Game;

using uint = unsigned int;

enum Father { ALIEN, PLAYER , BUNKER};

class Laser : public SceneObject
{
private:
	//Laser's direction
	static Vector2D<float> _dir;
	//Game's renderer
	SDL_Renderer* _myRenderer = nullptr;
	//Destination and size of the laser
	SDL_Rect _myRect;
	//velocidad de la bala
	Vector2D<float> _velocity;
	//Defines the father. 
	Father _father;

	int aux = 0;

public:
	Laser(Point2D<float> pos, Vector2D<float> velocity, std::pair<uint, uint> size, Game* game, SDL_Renderer* myRenderer,
		Father father);
	Laser(Game* game, SDL_Renderer* renderer, std::ifstream& in, std::pair<uint, uint> size, Vector2D<float> velocity);
	~Laser();

	//Game states
	void render() const override;
	void update() override;
	void save(std::ostream& out) const override;

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;

	//Getters
	bool getFather() const { return _father; };
	Vector2D<float> getVelocity() const { return _velocity; };
	std::pair<uint, uint> getSize() const { return _size; };
	SDL_Rect getRect() const { return _myRect; };

	//Setter 
	void setAux(int a) { aux = a; };
};