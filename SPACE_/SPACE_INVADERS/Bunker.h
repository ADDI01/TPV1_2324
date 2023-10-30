#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Bunker
{
private:
	Point2D<float> _pos;
	int _nVidas; //Tiene 4 vidas, cada golpe pierde 1 vida
	Texture* _texture;

public:
	//Constructores
	Bunker(): _pos(Vector2D<float>(0.f, 0.f)), _nVidas(0), _texture(nullptr) {};
	Bunker(Point2D<float> pos, int nVidas, Texture* texture): _pos(pos), _nVidas(nVidas), _texture(texture) {};

	//Destructor

};

