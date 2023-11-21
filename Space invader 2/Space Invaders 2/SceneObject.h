#pragma once
#include <iostream>
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"

class SceneObject: public GameObject 
{
protected:
	Point2D<float> pos;
	std::pair <int, int> dimensiones;
	int life;
	//falta un iterador de la lista de objetos de la escena

	virtual bool Hit(SDL_Rect AttackRect, int typeOfDamage) = 0; //tipeOfDamage se podrá cambiar por un enum
};

