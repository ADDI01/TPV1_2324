#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDLError.h"
#include <SDL.h>

using namespace std;

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
	uint _offset = 5;
	Point2D<float> _pos;
	pair<uint, uint> _size;
	SDL_Rect* _cannonRect = nullptr;
	SDL_Rect* _pointsRect = nullptr;
	Texture* _texture = nullptr;

public:
	//Constructor
	InfoBar(Game* game, Texture* texture, Point2D<float> pos, pair<uint, uint> size, uint points) : GameObject(game),
		_texture(texture), _points(points), _pos(pos), _size(size) {
		_cannonRect = new SDL_Rect;
		_pointsRect = new SDL_Rect;
	};
	~InfoBar() {
		delete _cannonRect; _cannonRect = nullptr; delete _pointsRect; _pointsRect = nullptr; _texture = nullptr;
	};

	void render() const override;
	void update() override {};
	void save(std::ostream& out) const override {};
	//Setter
	void setPoints(uint type);
};

