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
	ShooterAlien(Point2D<float> pos, Texture* texture, std::pair<uint, uint> size, Game* game,float velocity, int type, bool idle);

	//Game States
	void update() override;
	void save(std::ostream& out) const override;

	//Specific actions
	void fireLaser();
};

