#pragma once
#include "Vector2D.h"
#include "Texture.h"
class Game;
class Cannon
{
private:
	//Posición del cañón
	Point2D<float> _pos;
	int _nLifes;
	//Cool Down entre disparos
	float _shootCD;
	// puntero a su textura
	Texture* _myTexture;
	//puntero a la clase Game
	Game* _myGame;
	//Nº de vidas

public: 
	Cannon() : _pos(0, 0), _nLifes(0), _shootCD(0), _myTexture(nullptr), _myGame(nullptr) {};
	Cannon(Vector2D<float> pos, int nLifes, float shootCD, Texture* texture, Game* game) : _pos(pos), _nLifes(nLifes),
		_shootCD(shootCD), _myTexture(texture), _myGame(game) {};
	~Cannon();

	void render() const;
	void update();
	void Hit();
	void HandleEvents() ;
};

