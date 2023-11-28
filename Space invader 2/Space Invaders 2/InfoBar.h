#pragma once

#include "GameObject.h"

using uint = unsigned int;

class Game;

struct InfoData {
	uint yellowAlien = 30, greenAlien = 20, redAlien = 10;
	uint ufo = 100;
};

class InfoBar : public GameObject
{
private:
	uint _points = 0;

public:
	//Constructor
	InfoBar(Game* game, uint points) : GameObject(game), _points(points) {};
	~InfoBar() {};

	//Setter
	void setPoints() {};
};

