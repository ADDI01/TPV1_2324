#pragma once

#include "GameObject.h"

using uint = unsigned int;

class Game;

struct Points {
	uint yellowAlien = 30, greenAlien = 20, redAlien = 10;
	uint ufo = 100;
};

class InfoBar : public GameObject
{
private:
	uint _points = 0;
	Point2D<float> _pos;
	pair<uint, uint> _size;
	SDL_Rect* _myRect = nullptr;

public:
	//Constructor
	InfoBar(Game* game, Point2D<float> pos, pair<uint, uint> size, uint points) : GameObject(game), _points(points),
		_pos(pos), _size(size) {
		_myRect = new SDL_Rect; 
	};
	~InfoBar() { delete _myRect; _myRect = nullptr; };

	void render() const override;
	void update() override;

	//Setter
	void setPoints(uint type);
};

