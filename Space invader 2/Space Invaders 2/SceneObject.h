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
	list<SceneObject*>::iterator _it;

public:
	SceneObject(Game* game,Texture* texture, Point2D<float> pos, std::pair <uint, uint> size, int life) : 
		GameObject(game), _texture(texture), _pos(pos), _size(size), _life(life) {};
	virtual ~SceneObject() {};

	virtual void render() const = 0;
	virtual void update() = 0;

	virtual bool save() const = 0;
	//método que ejecutan los Objetos de la escena a ser golpeados
	virtual bool hit(SDL_Rect AttackRect, int typeOfDamage) = 0; //tipeOfDamage se podrá cambiar por un enum
	void setListIterator(list<SceneObject*>::iterator it) { _it = it; };
};

