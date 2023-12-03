#pragma once
#include"checkML.h"
#include <fstream>

// promesa de clase Game
class Game;

class GameObject
{
protected:
	//Punntero al juego
	Game* _game;

public:
	GameObject(Game* game): _game(game) {};
	virtual ~GameObject() {};

	//métodos virtuales puros para renderizar, actualizar y guardar los objetos

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void save(std::ostream& out) const = 0;
};
