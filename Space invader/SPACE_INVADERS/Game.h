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
	float cannonVelocity = 3;
	float cannonshootCD = 10;
	//Aliens
	int subType = -1; //0 shooter, 1 green, 2 red
	uint row, col;
	uint alienW = 48, alienH = 32;
	bool idle = false; //Frame to draw
	float alienDirection = 5; //direcci�n en el eje x a la que van todos los aliens
	bool alienCannotMove = false; // booleano que no permite moverse a los alien�genas
	vector <Alien*> aliens; //Aliens vector
	float alienVelocity = 2;
	//Bunkers
	uint bunkerLifes = 4;
	uint bunkerW = 90, bunkerH = 59;
	vector <Bunker*> bunkers; //Bunkers vector
	//Laser
	vector <Laser*> lasers; // vectos con los l�seres de juego
	Vector2D<float> laserVelocity = Vector2D<float>(0, 10);

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
	Star* star = nullptr;

	Texture* textures[NUM_TEXTURES];
	const char* texturePath[NUM_TEXTURES];

	//Condiciones partida
	bool exit = false;
	bool win = false;
	bool gameover = false;

public:
	Game();
	~Game() {
		for (Alien* a : tGameObjsProps.aliens) { delete a; a = nullptr; }
		for (Bunker* b : tGameObjsProps.bunkers) { delete b; b = nullptr; }
		for (Laser* l : tGameObjsProps.lasers) { delete l; l = nullptr; }
		for (Texture* t : textures) { delete t; t = nullptr; }
		delete cannon;
		delete renderer;
		delete window;
		//delete star;
	};
	void init();
	bool textureLoading();
	void loadFromFile();
	void loadCannon(ifstream& file);
	void loadBunkers(ifstream& file);
	void loadAliens(ifstream& file);
	void render() const;
	void update();
	void handleEvents();
	Vector2D<float> getDirection();
	void cannotMove();
	void run();
	int getRandomRange(int min, int max);
	void fireLaser(Alien* alien);
	vector <Alien*> getAliens() const { return tGameObjsProps.aliens; };
	vector <Bunker*> getBunker() const { return tGameObjsProps.bunkers; };
};

#endif 