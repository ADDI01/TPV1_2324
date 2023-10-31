#ifndef CANNON_H_
#define CANNON_H_

#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Game;

class Cannon
{
private:
	//Posición del cañón
	Point2D<float> _pos;
	//Cool Down entre disparos
	float _shootCD;
	// puntero a su textura
	Texture* _texture;
	//puntero a la clase Game
	Game* _myGame;
	//Nº de vidas
	uint _nLifes;
	//Tamaño del alien
	uint _w = 0, _h = 0;

public: 
	Cannon() : _pos(0, 0), _nLifes(0), _shootCD(0), _texture(nullptr), _myGame(nullptr), _w(0), _h(0) {};
	Cannon(Point2D<float> pos, uint nLifes, float shootCD, Texture* texture, Game* game, uint w, uint h) 
		: _pos(pos), _nLifes(nLifes), _shootCD(shootCD), _texture(texture), _myGame(game), _w(w), _h(h) {};
	~Cannon();

	void render() const;
	void update();
	void Hit();
	void HandleEvents() ;
};

#endif