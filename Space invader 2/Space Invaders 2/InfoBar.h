#pragma once

#include "GameObject.h"

using uint = unsigned int;

class Game;

class InfoBar : public GameObject
{
private:
	uint _points = 0;

public:
	//Constructor
	InfoBar(Game* game, uint points) : GameObject(game), _points(points) {};
	~InfoBar() {};

	//Setter
	void setPoints(uint p) { _points += p; };
};

