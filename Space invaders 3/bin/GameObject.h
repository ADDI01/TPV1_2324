#pragma once
#include"checkML.h"
#include "GameList.h"
#include <fstream>

// promesa de clase Game
class GameState;

class GameObject
{
protected:
	//Puntero al juego
	GameState* _game;
	GameList < GameObject, true>::anchor _it;

public:
	GameObject(GameState* game): _game(game) {};
	virtual ~GameObject() {};
	//m�todos virtuales puros para renderizar, actualizar y guardar los objetos

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void save(std::ostream& out) const = 0;
	void setListAnchor(GameList < GameObject, true>::anchor it) { _it = it; };
	GameList < GameObject, true>::anchor getListAnchor() { return _it; };
};