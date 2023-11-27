#pragma once
#include"checkML.h"
// promesa de clase Game
class Game;

class GameObject
{
protected:
	//Punntero al juego
	Game* _game;

	GameObject(Game* game) : _game(game) {};
	//virtual ~GameObject();

	//métodos virtuales puros para renderizar, actualizar y guardar los objetos

	virtual void render() const = 0;
	virtual bool update() = 0;
	
	virtual bool save() = 0;
};

