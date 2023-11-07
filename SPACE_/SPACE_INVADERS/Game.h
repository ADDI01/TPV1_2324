#ifndef GAME_H_
#define GAME_H_

#include <SDL.h>
#include "Vector2D.h"
#include "AliensMap.h"
#include "Alien.h"
#include "BunkersMap.h"
#include "Bunker.h"
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
const uint FRAME_RATE = 100;
const uint NUM_TEXTURES = 4;

struct {
	int tObject = -1; //0 Cannon, 1 Aliens, 2 Bunkers
	uint posX, posY; //GameOject position
	//Cannon
	uint cannonLifes = 4;
	float shootCD = 2.0f; //Shoot cooldown 
	uint cannonW = 34, cannonH = 21;
	//Aliens
	int subType = -1; //0 shooter, 1 green, 2 red
	uint row, col;
	uint alienW = 48, alienH = 32;
	bool idle = false; //Frame to draw
	vector <Alien*> aliens; //Aliens vector
	//Bunkers
	uint bunkerLifes = 4;
	uint bunkerW = 90, bunkerH = 59;
	vector <Bunker*> bunkers; //Bunkers vector
} tGameObjsProps;

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

	//Condiciones partida
	bool exit = false;
	bool win = false;
	bool gameover = false;

public:
	Game();
	//~Game();
	void init();
	bool textureLoading();
	void loadFromFile();
	void loadCannon(ifstream& file);
	void loadBunkers(ifstream& file);
	void loadAliens(ifstream& file);
	void render() const;
	void update();
	void run();

};

#endif 