#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

using uint = unsigned int;

class Star
{
private:
	//posición del background
	Point2D<float> _pos;
	//puntero a su Textura
	Texture* _texture;
	//Tamaño del alien
	std::pair<uint, uint> _size;

public:
	Star(Point2D<float> pos, Texture* texture, std::pair<uint, uint> size) : _pos(pos), _texture(texture), _size(size) {};

	void render() const {
		SDL_Rect destRect;
		destRect.x = 0;
		destRect.y = 0;
		destRect.w = _size.first;
		destRect.h = _size.second;

		_texture->render(destRect);
	};
};