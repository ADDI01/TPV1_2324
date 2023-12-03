#pragma once

#include "Vector2D.h"
#include "checkML.h"
#include "Texture.h"
#include "Mothership.h"
#include "SceneObject.h"

using uint = unsigned int;

using namespace std;

class Game;

//Shooter alien cooldowns
const float MIN_CD = 20, INT_CD = 60, MAX_CD = 100;

class Alien: public SceneObject
{
protected:
	//Alien's type
	int _subType = -1;
	//Alien's current frame to render. False 1st one, True 2nd one
	bool _idle = false;
	//Pointer to Game class
	Game* _myGame = nullptr;
	//Alien's speed
	float _velocity = 0.0f;
	//Destination and size of the alien
	SDL_Rect* _myRect = nullptr;
	//Shoot cooldown
	float _shootCD = 0.0f;
	//Pointer to Mothership
	Mothership* _mother = nullptr;
	
public:
	Alien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, float velocity, 
		int type, bool idle);
	~Alien();

	//Game states
	void render() const override;
	void update() override;
	void save(std::ostream& out) const override;

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override ;
	void bajaColumna();

	//Getters
	SDL_Rect* getRect() const { return _myRect; };
	uint getSubtype() const { return _subType; };
	Vector2D<float> getPosition() const { return _pos; };
	void setMother(Mothership* mother) { _mother = mother; };
};


