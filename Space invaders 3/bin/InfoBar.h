#pragma once

#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <SDL_ttf.h>
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
	int _points = 0;
	//Separation from the borders of the screen
	uint _offset = 5;
	//Infobar's position on the screen
	Point2D<float> _pos;
	//Infobar's size
	std::pair<uint, uint> _size;
	//Rects for the cannon lifes and points
	SDL_Rect _cannonLife1, _cannonLife2, _cannonLife3;
	SDL_Rect _pointsRect;
	//Font size
	uint _fontSize = 0;
	//Texture of the cannon
	Texture* _texture = nullptr;
	//Pointer of playstate
	PlayState* _myPlayState;
	//Text color
	SDL_Color color;
	//Pointer to font
	TTF_Font* font = nullptr;
	//Pointer to surface
	SDL_Surface* surf = nullptr;
	//Pointer to texture
	SDL_Texture* _pointsTexture = nullptr;
	//Pointer to renderer
	SDL_Renderer* _renderer = nullptr;

public:
	InfoBar(GameState* game, SDL_Renderer* renderer, PlayState* myPlayState, Texture* texture, Point2D<float> pos, std::pair<uint, 
		uint> size, uint points, uint fontSize);
	~InfoBar();

	//GameStates
	void render() const override;
	void update() override;
	void save(std::ostream& out) const override {};

	//Setter
	void setPoints(uint type);
};

