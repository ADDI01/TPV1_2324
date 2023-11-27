#pragma once
#include "SceneObject.h"

using uint = unsigned int;

class Alien: public SceneObject
{
private:
	//Pointer to texture
	Texture* _texture = nullptr;
	//Alien's speed
	float _velocity = 0.0f;
	//Destination and size of the alien
	SDL_Rect* _myRect = nullptr;
	//Shoot cooldown
	float _shootCD = 0.0f;
	//Alien's type
	int _subType = -1;
	//Alien's current frame to render. False 1st one, True 2nd one
	bool _idle = false;

public:
	Alien(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, float velocity, int type, bool idle);
	~Alien();

	//Game states
	void render() const override;
	bool update() override;
	bool save() override { return false; };

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	void bajaColumna();

	//Getters
	SDL_Rect* getRect() const { return _myRect; };
	uint getSubtype() const { return _subType; };
	Vector2D<float> getPosition() const { return pos; };
};

