#ifndef ALIEN_H_
#define ALIEN_H_

#include "Vector2D.h"
#include "Texture.h"

using uint = unsigned int;

class Game;

class Alien
{
private:
	//Direccion de los aliens
	static Vector2D<float> _dir;
	//posición de alienígena
	Point2D<float> _pos;
	// Tipo del alienígena, el enunciado dice que sea un int
	uint _subType;
	//Bool que controla en que parte de la animacion esta
	bool _idle;
	//puntero a su Textura
	Texture* _texture;
	//puntero a clase Game
	Game * _myGame;
	//Tamaño del alien
	uint _w = 0, _h = 0;
	//velocidad de los alienígenas
	float _velocity;
	//variable Rect para las colisiones
	SDL_Rect* _myRect = new SDL_Rect;

	public:
		Alien() : _pos(0,0), _subType(-1), _texture(nullptr), _myGame(nullptr), _w(0), _h(0), _velocity(0) {};
		Alien(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, float velocity, uint type, bool idle)
			: _pos(pos), _texture(texture), _myGame(game), _velocity(velocity), _w(w), _h(h), _subType(type), _idle(idle) {};
		~Alien();

		void bajaColumna();
		void render() const;
		bool update();
		void Hit();
		SDL_Rect* getRect() const { return _myRect; };
};

#endif

