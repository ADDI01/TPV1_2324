#pragma once
#include <list>
#include <string>
#include <SDL.h>
#include"checkML.h"
#include "Texture.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Ufo.h"
#include "Star.h"
#include "ShooterAlien.h"
#include "Laser.h"
#include "InfoBar.h"



using uint = unsigned int;
using namespace std;

// variables globales para la pantalla
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 100;
const uint NUM_TEXTURES = 5;

class Game
{
private:
	//Punteros a ventana y render
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	list<SceneObject* > objectsList;
	Mothership* mother = new Mothership(this);
	//Texturas
	enum TextureName { CANNONTEXTURE, ALIENSTEXTURE, BUNKERSTEXTURE, STARTEXTURE,UFOTEXTURE };
	struct TextureData {
		const char* texturePath; // Path de la textura
		pair<uint, uint> dimensiones; //n� de filas y columnas
		TextureData(const char* texturePath, pair<uint, uint> dimensiones): texturePath(texturePath), 
			dimensiones(dimensiones){};
		~TextureData() { texturePath = nullptr; }
	};
	Texture* textures[NUM_TEXTURES];  
	TextureData* dataTextures[NUM_TEXTURES];

	//Condiciones partida
	bool exit = false;
	bool win = false;
	bool gameOver = false;

	//Unique 
	Star* star;
	InfoBar* infoBar;


public:
	Game();
	~Game();

	//Pre-game
	void init();
	bool textureLoading();
	void loadFromFile();

	//Game states
	void run();
	void render() const;
	void update();
	void handleEvents();
	void lose();
	void fireLaser(SceneObject* object);

	//Getters
	int getRandomRange(int min, int max);
	uint getHeight() { return WIN_HEIGHT; };
	uint getWidth() { return WIN_WIDTH; };
};

