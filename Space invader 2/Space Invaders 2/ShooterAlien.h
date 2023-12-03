#pragma once
#include "Alien.h"
class ShooterAlien: public Alien
{
private:
	//Shooter alien cooldowns
	const float MIN_CD = 150, MAX_CD = 300;
	//Shoot cooldown
	float _shootCD;
public:
	ShooterAlien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, Mothership* mother,float velocity, int type, bool idle);

	bool update();

	void fireLaser();
};

