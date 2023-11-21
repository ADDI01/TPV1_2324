#pragma once
#include"checkML.h"
// promesa de clase Game
class Game;

class GameObject
{
protected:
	//Punntero al juego
	Game* _myGame;
	virtual ~GameObject();

	//métodos virtuales puros para renderizar, actualizar y guardar los objetos

	virtual bool Render() = 0;
	virtual bool Update() = 0;
	virtual bool Save() = 0;
};

