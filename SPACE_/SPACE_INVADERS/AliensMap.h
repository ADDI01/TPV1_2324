#ifndef ALIENSMAP_H_
#define ALIENSMAP_H_

#include "Vector2D.h"
#include "Texture.h"
#include "Alien.h"
#include <vector>

using uint = unsigned int;
using namespace std;

class AliensMap
{
private:
	//Textura de los búnkeres, todos la misma
	Texture* _alienTexture = nullptr;
	//Array dinámico de objetos tipo Bunker
	vector <Alien*> _aliens;
	//Nº de búnkeres que quedan
	uint _nAliens;
	//Cuanto ocupan las celdas de los bunkers
	uint _cellW = 0, _cellH = 0;
	//Ancho y alto del bunkersMap
	uint _w = 0, _h = 0;
	//Numero de filas y columnas del bunkersMap
	uint _rows = 0, _cols = 0;
	//Posicion inicio del blocksMap
	Point2D<float> _pos;
public:
	AliensMap() : _alienTexture(nullptr), _pos(0, 0)
	{
		_nAliens = _cellW = _cellH = _w = _h = _rows = _cols = 0;
	};
	AliensMap(Texture* texture, vector <Alien*>& aliens, uint nAliens, uint cellW, uint cellH, uint w, 
		uint h, uint rows, uint cols, Point2D<float> pos) 
		: _alienTexture(texture), _aliens(aliens), _nAliens(nAliens), _cellW(cellW), _cellH(cellH), 
		_w(w), _h(h), _rows(rows), _cols(cols), _pos(pos) { };

	void render() const;
	void update();
};

#endif