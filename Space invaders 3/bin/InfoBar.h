#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <SDL.h>

using uint = unsigned int;

class PlayState;

struct Points {
	uint yellowAlien = 30, greenAlien = 20, redAlien = 10;
	uint ufo = 100;
};

class InfoBar : public GameObject
{
private:
	//Game puntuation
	uint _points = 0;
	//Separation from the borders of the screen
	uint _offset = 5;
	//Infobar's position on the screen
	Point2D<float> _pos;
	//Infobar's size
	std::pair<uint, uint> _size;
	//Rects for the cannon lifes and points
	SDL_Rect _cannonLife1, _cannonLife2, _cannonLife3;
	SDL_Rect _pointsRect;
	//Texture of the cannon
	Texture* _texture = nullptr;
	//Pointer of playstate
	PlayState* _myPlayState;

public:
	InfoBar(GameState* game, PlayState* myPlayState, Texture* texture, Point2D<float> pos, std::pair<uint, uint> size, uint points);
	~InfoBar();

	//GameStates
	void render() const override;
	void update() override {}; //TODO: ACTUALIZAR LA PUNTUACION PARA QUE SE PRINTEE
	void save(std::ostream& out) const override {};

	//Setter
	void setPoints(uint type);
};

