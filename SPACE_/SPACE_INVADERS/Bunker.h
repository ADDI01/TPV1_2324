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
	//Numero de filas y columnas del bunkersMap
	uint _rows = 0, _cols = 0;

public:
	//Constructores
	Bunker() : _pos(0,0), _texture(nullptr), _w(0), _h(0), _nLifes(0), _rows(0), _cols(0) {};
	Bunker(Point2D<float> pos, Texture* texture, uint w, uint h, uint nLifes, uint rows, uint cols)
		: _pos(pos), _texture(texture), _w(w), _h(h), _nLifes(nLifes), _rows(rows), _cols(cols) {};
	//~Bunker() { /*delete _texture; */ };

	void render() const;
	bool update();
	void hit();
	//Destructor
};

