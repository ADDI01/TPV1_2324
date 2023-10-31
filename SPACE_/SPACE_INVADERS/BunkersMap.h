#pragma once
#include "Bunker.h"
#include "Texture.h"
using uint = unsigned int;
class BunkersMap
{
private:
	//Textura de los búnkeres, todos la misma
	Texture* _bunkerTexture = nullptr;
	//Array dinámico de objetos tipo Bunker
	Bunker** _bunkers = nullptr;
	//Nº de búnkeres que quedan
	int _nBunkers, _nLifes;
	//Cuanto ocupan las celdas de los bunkers
	uint _cellW, _cellH;

public:
	BunkersMap() : _bunkerTexture(nullptr), _bunkers(nullptr) {};
	BunkersMap(Texture* texture, int nBunkeres,uint cellW, uint cellH, int nLifes): _bunkerTexture(texture), _nBunkers(nBunkeres),
		_cellW(cellW), _cellH(cellH), _nLifes(nLifes) { Load(); };
	void Load();

};

