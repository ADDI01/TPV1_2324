#include "SDLApplication.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"

using namespace std;

SDLApplication::~SDLApplication(){
	for (Texture* t : textures) { delete t; t = nullptr; }
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void SDLApplication::init(){
	// We first initialize SDL
// Inicializar SDL, crear ventana y renderizador
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr) {
		throw SDLError("Error loading SDL window or renderer");
	}

	if (!textureLoading())
		throw SDLError("No se cargaron las texturas.");
		/*
		hay que moverlo
		loadFromFile("../images/mapas/map" + to_string(nLevel % nLevels) + ".txt"); ç
		*/

}

bool SDLApplication::textureLoading()
{
	// main menu texture inicialization
	dataTextures[MAINMENUTEXTURE] = new TextureData("./recursos/fondos/mainMenu.png", pair<uint, uint>(1, 1));

	// cannon's texture inicialization
	dataTextures[CANNONTEXTURE] = new TextureData("./recursos/images/spaceship.png", pair<uint, uint>(1, 1));

	//alien's texture inicialization
	dataTextures[ALIENSTEXTURE] = new TextureData("./recursos/images/aliens.png", pair<uint, uint>(3, 2));

	//bunker's texture inicialization
	dataTextures[BUNKERSTEXTURE] = new TextureData("./recursos/images/bunker.png", pair<uint, uint>(1, 4));

	//bunker's texture inicialization
	dataTextures[STARTEXTURE] = new TextureData("./recursos/images/stars.png", pair<uint, uint>(1, 1));

	//Ufo's texture
	dataTextures[UFOTEXTURE] = new TextureData("./recursos/images/ufo.png", pair<uint, uint>(1, 2));

	// bomb texture inicialization
	dataTextures[BOMBTEXTURE] = new TextureData("./recursos/objetos/bomb.png", pair<uint, uint>(1, 1));

	// shield texture inicialization
	dataTextures[SHIELDTEXTURE] = new TextureData("./recursos/objetos/shield.png", pair<uint, uint>(1, 1));

	// shield reward texture inicialization
	dataTextures[SHIELDREWARDTEXTURE] = new TextureData("./recursos/objetos/shield_reward.png", pair<uint, uint>(1, 1));

	//Now, we create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		textures.push_back(new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second));
	}
	for (TextureData* d : dataTextures) { delete d; d = nullptr; }
	return true;
}

void SDLApplication::run()
{
	//while (true) {
	//}
}
