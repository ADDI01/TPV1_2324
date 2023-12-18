#pragma once
#include"checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDLApplication.h"
#include <list>
#include <iostream>

using uint = unsigned int;
class PlayState;

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
	GameList<SceneObject, false>::anchor _itS;
	//Estado de juego, es el mismo que su GameState, pero habría que castear para cogerlo si no se usan 2 parámtros distintos
	PlayState* _myPlayState;
	//Puntero a la Aplicación
	SDLApplication* _myApp;

public:
	SceneObject(GameState* game, PlayState* myPlayState, SDLApplication* app, Texture* texture, Point2D<float> pos, std::pair <uint, uint> size, int life) :
		GameObject(game), _texture(texture), _pos(pos), _size(size), _life(life), _myPlayState(myPlayState), _myApp(app){}; 
	SceneObject(GameState* game, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture);
	//Constructor for SceneObjects with default lifes
	SceneObject(GameState* game, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture, int life);
	SceneObject(GameState* game, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, std::pair<uint, uint> size, int life); //Constructor for laser
	virtual ~SceneObject() {};

	//Game States
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void save(std::ostream& out) const = 0;

	//Specific actions
	virtual bool hit(SDL_Rect AttackRect, int typeOfDamage) = 0;
	void setListAnchor(GameList < SceneObject, false>::anchor it) { _itS = it; };
};

