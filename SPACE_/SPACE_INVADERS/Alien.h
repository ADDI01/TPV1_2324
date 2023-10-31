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
	//Fila y columna en la que se encuentra en el aliensMap
	uint _rows = 0, _cols = 0;
	 
	public:
		Alien() : _pos(0,0), _subType(-1), _texture(nullptr), _myGame(nullptr), _w(0), _h(0), _rows(0), _cols(0) {};
		Alien(Point2D<float> pos, uint type, Texture* texture, Game* game, uint w, uint h, uint rows, uint cols, bool idle) 
			: _pos(pos), _subType(type), _texture(texture), _myGame(game), _w(w), _h(h), _rows(rows), _cols(cols),
					_idle(idle) {};
		~Alien();

		void render() const;
		bool update();
		void Hit();

};

#endif

