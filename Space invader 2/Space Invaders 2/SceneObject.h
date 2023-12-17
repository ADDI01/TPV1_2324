#pragma once

#include"checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <list>
#include <iostream>

using uint = unsigned int;

class SceneObject: public GameObject 
{
protected:
	//Position of the SceneObject
	Point2D<float> _pos;
	//Size of the SceneObject
	std::pair <int, int> _size;
	//Current lifes
	int _life;
	//Pointer to texture
	Texture* _texture = nullptr;
	//Iterator to the SceneObject in the list of SceneObjects
	std::list<SceneObject*>::iterator _it;

public:
	SceneObject(Game* game,Texture* texture, Point2D<float> pos, std::pair <uint, uint> size, int life) : 
		GameObject(game), _texture(texture), _pos(pos), _size(size), _life(life) {};
	SceneObject(Game* game, std::ifstream& in, Texture* texture);
	SceneObject(Game* game, std::ifstream& in, Texture* texture, int life); //Constructor for SceneObjects with default lifes
	SceneObject(Game* game, std::ifstream& in, std::pair<uint, uint> size, int life); //Constructor for laser
	virtual ~SceneObject() {};

	//Game States
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void save(std::ostream& out) const = 0;

	//Specific actions
	virtual bool hit(SDL_Rect AttackRect, int typeOfDamage) = 0;
	void setListIterator(std::list<SceneObject*>::iterator it) { _it = it; };

	//Getters
	Point2D<float> getPos() const { return _pos; };
};

