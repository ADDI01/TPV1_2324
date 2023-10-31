#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Bunker
{
private:
	Point2D<float> _pos;
	int _nLifes; //Tiene 4 vidas, cada golpe pierde 1 vida
	Texture* _texture;

public:
	//Constructores
	Bunker() : _pos(0,0), _nLifes(0), _texture(nullptr) {};
	Bunker(Point2D<float> pos,int nLifes, Texture* texture) : _pos(pos), _nLifes(nLifes), _texture(texture) {};
	~Bunker() { delete _texture; };

	void render()const;
	bool update();
	void hit();
	//Destructor
};

