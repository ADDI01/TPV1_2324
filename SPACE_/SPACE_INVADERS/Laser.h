#pragma once

#include "Vector2D.h"
#include "Texture.h"
class Game;
class Laser
{
private:
	//instancia de la clase Game
	Game* _myGame;
	// renderer de game
	SDL_Renderer* _myrenderer;
	//posición de la bala
	Point2D<float> _pos;
	//velocidad de la bala
	Vector2D<float> _velocity;
	// Booleano que define si la bala es del player o del enemigo, true = player, false = enemigo
	bool _fatherPlayer;

public:
	Laser() : _pos(0, 0), _velocity(0, 0), _fatherPlayer(false), _myGame(nullptr), _myrenderer(nullptr){};
	Laser(Point2D<float> pos, Vector2D<float> velocity, bool soyDelPlayer, Game* game, SDL_Renderer* myRender): _pos(pos), 
		_velocity(velocity), _fatherPlayer(_fatherPlayer), _myGame(game), _myrenderer(myRender){};

	void render() const;
	bool update();

};

