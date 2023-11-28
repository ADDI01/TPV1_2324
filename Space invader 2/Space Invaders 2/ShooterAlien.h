#pragma once
#include "Alien.h"
class ShooterAlien: public Alien
{
private:
	//Shooter alien cooldowns
	const float MIN_CD = 50, MAX_CD = 150;
	//Shoot cooldown
	float _shootCD = 0.0f;
public:
	ShooterAlien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game,
		float velocity, int type, bool idle) : Alien(pos,texture,size,game,velocity,type,idle){};

	bool update();
};

