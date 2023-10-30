#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"

#include <exception>
#include <string>   


using namespace std;

using uint = unsigned int;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 4;
const int FRAME_RATE = 5;

enum TextureName { CANNONTEXTURE, ALIENSMAPTEXTURE, BUNKERTEXTURE, STARSTEXTURE};
	
class Game
{
private:
	//Punteros a ventana y render
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	//Puntero por cada objeto del juego
	Alien* alien = nullptr;
	Bunker* bunker = nullptr;
	Cannon* cannon = nullptr;
	Laser* laser = nullptr;

	Texture* textures[NUM_TEXTURES];
	const char* texturePath[NUM_TEXTURES];

public:
	Game() { init(); };
	~Game();
	void init();
};

#endif 

