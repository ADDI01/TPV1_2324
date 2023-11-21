#ifndef STAR_H_
#define STAR_H_

#include "Vector2D.h"
#include "Texture.h"

using namespace std;
using uint = unsigned int;

class Star
{
private:
	//posición del background
	Point2D<float> _pos;
	//puntero a su Textura
	Texture* _texture;
	//Tamaño del alien
	uint _w = 0, _h = 0;

public:
	Star() : _pos(0, 0), _texture(nullptr), _w(0), _h(0) {};
	Star(Point2D<float> pos, Texture* texture, uint w, uint h) : _pos(pos), _texture(texture), _w(w), _h(h) {};

	void render() const;
};

#endif
