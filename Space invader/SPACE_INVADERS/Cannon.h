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
	//Vector de movimiento
	Vector2D<float> _direction;
	//Velocidad de la nave
	float _velocity;

public: 
	Cannon() : _pos(0, 0), _texture(nullptr), _w(0), _h(0), _myGame(nullptr), _nLifes(0), _shootCD(0) {};
	Cannon(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, uint nLifes, float shootCD)
		: _pos(pos), _texture(texture), _w(w), _h(h),_myGame(game), _nLifes(nLifes), _shootCD(shootCD) {};
	~Cannon();

	void render() const;
	void update();
	void Hit();
	void handleEvents(Vector2D<float> direction);
};

#endif