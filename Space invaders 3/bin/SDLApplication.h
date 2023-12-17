#pragma once
#include <SDL.h>
#include "checkML.h"
#include "texture.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include <vector>

using uint = unsigned int;

//Global game variables
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint FRAME_RATE = 25;
const uint NUM_TEXTURES = 18;

class SDLApplication
{
	//Window and render pointers
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	GameStateMachine _myStateMachine;


	//Texture's ID
	enum TextureName { MAINMENUTEXTURE, CANNONTEXTURE, ALIENSTEXTURE, BUNKERSTEXTURE, STARTEXTURE, UFOTEXTURE, BOMBTEXTURE, SHIELDTEXTURE, SHIELDREWARDTEXTURE 
	, CARGARPARTIDA, CODIGO, CONTINUAR, GAMEOVER, GUARDARPARTIDA, HASGANADO,NUEVAPARTIDA,SALIR, VOLVERALMENU};
	//Textures info
	struct TextureData {
		const char* texturePath; // Path de la textura
		std::pair<uint, uint> dimensiones; //n� de filas y columnas
		TextureData(const char* texturePath, std::pair<uint, uint> dimensiones) : texturePath(texturePath),
			dimensiones(dimensiones) {};
		~TextureData() { texturePath = nullptr; }
	};
	std::vector<Texture*> textures;
	TextureData* dataTextures[NUM_TEXTURES];

	bool exit = false;

public:
	SDLApplication() {};
	~SDLApplication();

	//Pre-game
	void init();
	bool textureLoading();

	//Game states
	void run();
	//void updateState();
	void exitGame();
	void pushState(GameState* gS);

	//getters & setters
	uint getHeight() const { return WIN_HEIGHT; };
	uint getWidth() const { return WIN_WIDTH; };
	SDL_Renderer* getRenderer() const { return renderer; };
	SDL_Window* getWindow() const { return window; };
	void setExit() { exit = true; };
	std::vector<Texture*> getTexture() { return textures; };
};