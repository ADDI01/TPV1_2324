#pragma once
#include "Vector2D.h"
#include "Texture.h"

class Game;
class Alien
{
	private:
	//posición de alienígena
	Point2D<float> _pos;
	// Tipo del alienígena, el enunciado dice que sea un int
	int _subType;
	//puntero a su Textura
	Texture* _myTexture;
	//puntero a clase Game
	Game * _myGame;
	 
	public:
		Alien() : _pos(0,0), _subType(0), _myTexture(nullptr), _myGame(nullptr) {};
		Alien(Point2D<float> pos, int  type, Texture* texture, Game* game) : _pos(pos), _subType(type), _myTexture(texture), _myGame(game) {};
		~Alien();

		void render() const;
		bool update();
		void Hit();

};

