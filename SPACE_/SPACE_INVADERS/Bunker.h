#ifndef BUNKER_H_
#define BUNKER_H_


#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Bunker
{
private:
	Point2D<float> _pos;
	int _nLifes; //Tiene 4 vidas, cada golpe pierde 1 vida
	Texture* _texture = nullptr;
	//Tamaño del Bunker
	uint _w = 0;
	uint _h = 0;
	//Fila y columna en el bunkersMap
	uint _rows = 0;
	uint _cols = 0;


public:
	//Constructores
	Bunker() : _pos(0,0), _nLifes(0), _texture(nullptr), _rows(0), _cols(0), _w(0), _h(0) {};
	Bunker(Point2D<float> pos,int nLifes, Texture* texture, uint rows, uint cols, uint w, uint h) 
		: _pos(pos), _nLifes(nLifes), _texture(texture), _rows(rows), _cols(cols), _w(w), _h(h) {};
	~Bunker() { /*delete _texture;*/ };

	void render() const;
	bool update();
	void hit();
};

#endif
