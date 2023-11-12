#pragma once

#include "Vector2D.h"
#include "Texture.h"

using namespace std;
using uint = unsigned int;

class Bunker
{
private:
	Point2D<float> _pos;
	uint _nLifes; //Tiene 4 vidas, cada golpe pierde 1 vida
	Texture* _texture;
	//Ancho y alto del bunker
	uint _w = 0, _h = 0;


public:
	//Constructores
	Bunker() : _pos(0,0), _texture(nullptr), _w(0), _h(0), _nLifes(0){};
	Bunker(Point2D<float> pos, Texture* texture, uint w, uint h, uint nLifes)
		: _pos(pos), _texture(texture), _w(w), _h(h), _nLifes(nLifes){};
	//~Bunker() { /*delete _texture; */ };

	void render() const;
	bool update();
	void hit();
	//Destructor
};
