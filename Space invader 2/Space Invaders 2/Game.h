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
#include <vector>
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"

using uint = unsigned int;

//Global game variables
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 25;
const uint NUM_TEXTURES = 5;

class Game
{
private:
	//Window and render pointers
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//SceneObject's list
	std::list<SceneObject* > objectsList;
	//SceneObject's list to delete
	std::list<std::list<SceneObject*>::iterator> objectsToDelete;

	//SceneObject's pointers
	Mothership* mother = nullptr;
	Cannon* _cannon = nullptr;
	Star* star = nullptr;
	InfoBar* infoBar = nullptr;

	//Texture's ID
	enum TextureName { CANNONTEXTURE, ALIENSTEXTURE, BUNKERSTEXTURE, STARTEXTURE,UFOTEXTURE };
	//Textures info
	struct TextureData {
		const char* texturePath; // Path de la textura
		std::pair<uint, uint> dimensiones; //n� de filas y columnas
		TextureData(const char* texturePath, std::pair<uint, uint> dimensiones): texturePath(texturePath),
			dimensiones(dimensiones){};
		~TextureData() { texturePath = nullptr; }
	};
	std::vector<Texture*> textures;
	TextureData* dataTextures[NUM_TEXTURES];

	//Game conditions
	bool exit = false;
	bool win = false;
	bool gameOver = false;
	bool pauseSave = false; //para guardar 
	bool pauseCharge = false; // para cargar

	//Specific atributes
	int nLevel = 0;
	const int nLevels = 3;
	float _landedHeight = 0;

public:
	Game() {};
	~Game();

	//Pre-game
	void init();
	bool textureLoading();
	void loadFromFile(std::string fileName);

	//Game states
	void run();
	void render() const;
	void update();
	void save(int k) const;
	void handleEvents();
	void lose();
	void win();

	//Specific actions
	void addToList(SceneObject* object);
	bool damage(SDL_Rect rect, Father father) const;
	void hasDie(std::list<SceneObject*>::iterator it);
	void limpiaLista();

	//Getters
	uint getCannonLifes() { return _cannon->getnLifes(); };
	int getRandomRange(int min, int max);
	uint getHeight() { return WIN_HEIGHT; };
	uint getWidth() { return WIN_WIDTH; };
	SDL_Renderer* getRenderer() { return renderer; };
	SDL_Window* getWindow() { return window; };
	float getLandedHeight() { return _landedHeight; };
};

