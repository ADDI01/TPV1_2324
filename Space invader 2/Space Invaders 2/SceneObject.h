#pragma once
#include"checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <list>
#include <iostream>

using namespace std;

using uint = unsigned int;

class SceneObject: public GameObject 
{
protected:
	Point2D<float> _pos;
	pair <uint, uint> _size;
	int _life;
	//falta un iterador de la lista de objetos de la escena
	list<SceneObject>::iterator it;

<<<<<<< Updated upstream
	SceneObject(Game* game, Point2D<float> pos, std::pair <int, int> dimensiones, int life) : GameObject(game), pos(pos), dimensiones(dimensiones), life(life) {};

	//método que ejecutan los Objetos de la escena a ser golpeados
	virtual bool hit(SDL_Rect AttackRect, int typeOfDamage) = 0; //tipeOfDamage se podrá cambiar por un enum
=======
	virtual void render() = 0;
	virtual void setListIterator() = 0; //Definir
	//método que ejecutan los Objetos de la escena a ser golpeados
	virtual bool hit(SDL_Rect attackRect, int typeOfDamage) = 0; //tipeOfDamage se podrá cambiar por un enum

	//Constructor
	SceneObject(Point2D<float> pos, pair<uint, uint> size, int life) : _pos(pos), _size(size), _life(life) {};
>>>>>>> Stashed changes
};

