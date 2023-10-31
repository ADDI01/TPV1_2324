#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include <list>
#include "Vector2D.h"
#include "AliensMap.h"
#include "BunkersMap.h"
#include "Laser.h"
#include "Cannon.h"
#include "Star.h"
#include "Texture.h"
#include "checkML.h"
#include <exception>
#include <iostream>
#include <string>  

using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 4;
const int FRAME_RATE = 5;

enum TextureName { CANNONTEXTURE, ALIENSMAPTEXTURE, BUNKERSMAPTEXTURE, STARTEXTURE};

class Game
{
private:
	//Punteros a ventana y render
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	//Puntero por cada objeto del juego
	Cannon* cannon = nullptr;
	AliensMap* aliensMap = nullptr;
	BunkersMap* bunkersMap = nullptr;
	Star* star = nullptr;

	Texture* textures[NUM_TEXTURES];
	const char* texturePath[NUM_TEXTURES];

public:
	Game() ;
	//~Game();
	void init();
	void render();
	void update();
};

#endif 