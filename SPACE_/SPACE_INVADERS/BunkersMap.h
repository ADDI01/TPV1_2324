#ifndef BUNKERSMAP_H_
#define BUNKERSSMAP_H_

#include "Bunker.h"
#include "Texture.h"
#include <vector>

using namespace std;
using uint = unsigned int;

class BunkersMap
{
private:
	//Textura de los búnkeres, todos la misma
	Texture* _bunkerTexture = nullptr;
	//Array dinámico de objetos tipo Bunker
	vector<Bunker*> _bunkers;
	//Nº de búnkeres que quedan
	uint _nBunkers, _nLifes;
	//Cuanto ocupan las celdas de los bunkers
	uint _cellW = 0, _cellH = 0;
	//Ancho y alto del bunkersMap
	uint _w = 0, _h = 0; 
	//Numero de filas y columnas del bunkersMap
	uint _rows = 0, _cols = 0; 
	//Posicion inicio del blocksMap
	Point2D<float> _pos;

public:
	BunkersMap() : _bunkerTexture(nullptr), _pos(0, 0) 
	{ _nBunkers = _nLifes = _cellW = _cellH = _w = _h = _rows = _cols = 0; };
	BunkersMap(Texture* texture, vector<Bunker*>& bunkers, uint nBunkeres, uint nLifes, uint cellW, 
		uint cellH, uint w, uint h, uint rows, uint cols, Point2D<float> pos) 
		: _bunkerTexture(texture), _bunkers(bunkers), _nBunkers(nBunkeres), _nLifes(nLifes),
		_cellW(cellW), _cellH(cellH), _w(w), _h(h), _rows(rows), _cols(cols),  _pos(pos) { };

	void render() const;
};

#endif