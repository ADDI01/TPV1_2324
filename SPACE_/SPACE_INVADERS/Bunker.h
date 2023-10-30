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
	Bunker() : _pos(0,0), _nVidas(0), _texture(nullptr) {};
	Bunker(Point2D<float> pos, Texture* texture) : _pos(pos), _nVidas(4), _texture(texture) {};
	~Bunker() { delete _texture; };

	void render()const;
	bool update();
	void hit();
	//Destructor
};

