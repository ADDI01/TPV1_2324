#ifndef ALIEN_H_
#define ALIEN_H_

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
private:
	//Alien's type
	int _subType = -1;
	//Alien's current frame to render. False 1st one, True 2nd one
	bool _idle = false;
	//Pointer to texture
	Texture* _texture = nullptr;
	//Pointer to Game class
	Game* _myGame = nullptr;
	//Pointer to Mothership
	Mothership* _mother = nullptr;
	//Alien's speed
	float _velocity = 0.0f;
	//Destination and size of the alien
	SDL_Rect* _myRect = nullptr;
	//Shoot cooldown
	float _shootCD = 0.0f;

public:
	Alien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, Mothership* mother, float velocity, 
		int type, bool idle);
	~Alien();

	//Game states
	void render() const override;
	bool update() override;
	bool save() override { return false; };

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	
public:
	Alien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, Mothership* mother,
		float velocity, int type, bool idle);
	~Alien();

	//Game states
	void render() const override;
	bool update();

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage);
	//void bajaColumna();

	//Getters
	SDL_Rect* getRect() const { return _myRect; };
	uint getSubtype() const { return _subType; };
	Vector2D<float> getPosition() const { return _pos; };
};

#endif



