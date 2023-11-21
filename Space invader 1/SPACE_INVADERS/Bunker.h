#ifndef BUNKER_H_
#define BUNKER_H_

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"

using uint = unsigned int;

class Bunker
{
private:
	//Bunker's position
	Point2D<float> _pos;
	//Bunker's lifes
	int _nLifes = 0;
	//Pointer to texture
	Texture* _texture;
	//Bunker's size
	uint _w = 0, _h = 0;
	//Destination and size of the bunker
	SDL_Rect* _myRect = nullptr;

public:
	Bunker(Point2D<float> pos, Texture* texture, uint w, uint h, uint nLifes);
	~Bunker();

	//Game states
	void render() const;
	bool update();

	//Specific actions
	void hit();

	//Getters
	SDL_Rect* getRect() const { return _myRect; };
};

#endif