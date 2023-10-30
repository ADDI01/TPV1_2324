#pragma once

#include "Vector2D.h"
#include "Texture.h"
class Game;
class Laser
{
private:
	//instancia de la clase Game
	Game* _myGame;
	//posición de la bala
	Point2D<float> _pos;
	//velocidad de la bala
	Vector2D<float> _velocity;
	// Booleano que define si la bala es del player o del enemigo, true = player, false = enemigo
	bool _soyDelPlayer;
	Texture* _texture;
	Laser() : _pos(0, 0), _velocity(0, 0), _soyDelPlayer(false), _myGame(nullptr) {};
	Laser(Point2D<float> pos, Vector2D<float> velocity, bool soyDelPlayer, Game* game): _pos(pos), _velocity(velocity), _soyDelPlayer(_soyDelPlayer), _myGame(game) {};
	~Laser() { delete _texture; };

	void render() const;
	bool update();

};

