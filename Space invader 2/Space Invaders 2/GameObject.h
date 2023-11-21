#pragma once

// promesa de clase Game
class Game;

class GameObject
{
protected:
	//Punntero al juego
	Game* _myGame;
	virtual ~GameObject();

	//métodos virtuales puros
	virtual bool Render() = 0;
	virtual bool Update() = 0;
	virtual bool Save() = 0;
};

