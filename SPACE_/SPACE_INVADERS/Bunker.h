#pragma once

#include "Vector2D.h"
#include "Texture.h"

class Bunker
{
private:
	Point2D<float> _pos;
	int _nLifes; //Tiene 4 vidas, cada golpe pierde 1 vida
	Texture* _texture;
	//Cuanto ocupan las celdas de los bunkers
	uint _cellW = 0, _cellH = 0;
	//Ancho y alto del bunker
	uint _w = 0, _h = 0;
	//Numero de filas y columnas del bunkersMap
	uint _rows = 0, _cols = 0;

public:
	//Constructores
	Bunker() : _pos(0,0), _nLifes(0), _texture(nullptr), _cellW(0), _cellH(0), _w(0), _h(0), _rows(0), _cols(0) {};
	Bunker(Point2D<float> pos,int nLifes, Texture* texture, uint cellW, uint cellH, uint w, uint h, uint rows, uint cols) : _pos(pos),
		_nLifes(nLifes), _texture(texture), _cellW(cellW), _cellH(cellH), _w(w), _h(h), _rows(rows), _cols(cols) {};
	~Bunker() { delete _texture; };

	void render()const;
	bool update();
	void hit();
	//Destructor
};

