#pragma once
#include"checkML.h"
#include <SDL.h>
#include "Texture.h"
#include "Alien.h"
#include "Bunker.h"
#include<string>

using uint = unsigned int;
using namespace std;

// variables globales para la pantalla
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 100;
const uint NUM_TEXTURES = 4;

class Game
{
private:
	//Punteros a ventana y render
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Alien* alien;
	Bunker* bunker;

	//Texturas
	enum TextureName { CANNONTEXTURE, ALIENSTEXTURE, BUNKERSTEXTURE, STARTEXTURE };
	struct TextureData {
		const char* texturePath; // Path de la textura
		pair<uint, uint> dimensiones; //nº de filas y columnas
		TextureData(const char* texturePath, pair<uint, uint> dimensiones): texturePath(texturePath), dimensiones(dimensiones){};
	};
	Texture* textures[NUM_TEXTURES];
	TextureData* dataTextures[NUM_TEXTURES];
	

	//Condiciones partida
	bool exit = false;
	bool win = false;
	bool gameOver = false;

public:
	Game();
	//~Game();

	//Pre-game
	void init();
	bool textureLoading();
	//void loadFromFile();

	//Game states
	void run();
	void render() const;
	void update();
	//void handleEvents();
	//void lose();


	//Getters
	int getRandomRange(int min, int max);
	uint getHeight() { return WIN_HEIGHT; };
	uint getWidth() { return WIN_WIDTH; };
};

