#pragma once
#include"checkML.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <iostream>

class SceneObject: public GameObject 
{
protected:
	Point2D<float> pos;
	std::pair <int, int> dimensiones;
	int life;
	//falta un iterador de la lista de objetos de la escena

	//método que ejecutan los Objetos de la escena a ser golpeados
	virtual bool Hit(SDL_Rect AttackRect, int typeOfDamage) = 0; //tipeOfDamage se podrá cambiar por un enum
};

