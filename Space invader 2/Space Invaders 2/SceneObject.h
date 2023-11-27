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
	pair <int, int> _size;
	int _life;
	//Pointer to texture
	Texture* _texture = nullptr;
	//list<SceneObject>::iterator it;

	SceneObject(Game* game,Texture* texture, Point2D<float> pos, std::pair <uint, uint> dimensiones, int life) : GameObject(game), _texture(texture),
		_pos(pos), _size(dimensiones), _life(life) {};

	//método que ejecutan los Objetos de la escena a ser golpeados
	virtual bool hit(SDL_Rect AttackRect, int typeOfDamage) = 0; //tipeOfDamage se podrá cambiar por un enum

	//virtual void setListIterator(/* TODO: PONER PARAMTERO */) = 0;
};

