#include "SDLApplication.h"
#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "PlayState.h"
#include "PauseState.h"
#include "SDLError.h"

using namespace std;

SDLApplication::~SDLApplication(){
	for (Texture* t : textures) { delete t; t = nullptr; }
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void SDLApplication::init(){
	
	// We first initialize SDL
	// Inicializar SDL y TTF, crear ventana y renderizador
	TTF_Init();
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
		loadFromFile("../images/mapas/map" + to_string(nLevel % nLevels) + ".txt");
		*/
	MainMenuState* _mainMenu = new MainMenuState(this, textures[MAINMENUTEXTURE], textures[CONTINUAR], textures[CARGARPARTIDA], textures[SALIR]);
	_myStateMachine.pushState(_mainMenu);
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
	// CargarPartidatexture inicialization
	dataTextures[CARGARPARTIDA] = new TextureData("./recursos/textos/cargarPartida.png", pair<uint, uint>(1, 1));
	// Código texture inicialization
	dataTextures[CODIGO] = new TextureData("./recursos/textos/codigo.png", pair<uint, uint>(1, 1));
	// Continuar texture inicialization
	dataTextures[CONTINUAR] = new TextureData("./recursos/textos/continuar.png", pair<uint, uint>(1, 1));
	// game over texture inicialization
	dataTextures[GAMEOVER] = new TextureData("./recursos/textos/gameOver.png", pair<uint, uint>(1, 1));
	// guardar partida texture inicialization
	dataTextures[GUARDARPARTIDA] = new TextureData("./recursos/textos/guardarPartida.png", pair<uint, uint>(1, 1));
	// has ganado texture inicialization
	dataTextures[HASGANADO] = new TextureData("./recursos/textos/hasGanado.png", pair<uint, uint>(1, 1));
	// nueva partido texture inicialization
	dataTextures[NUEVAPARTIDA] = new TextureData("./recursos/textos/nuevaPartida.png", pair<uint, uint>(1, 1));
	// salir texture inicialization
	dataTextures[SALIR] = new TextureData("./recursos/textos/salir.png", pair<uint, uint>(1, 1));
	// volver al menu texture inicialization
	dataTextures[VOLVERALMENU] = new TextureData("./recursos/textos/volverAlMenu.png", pair<uint, uint>(1, 1));

	//Now, we create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		textures.push_back(new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second));
	}
	for (TextureData* d : dataTextures) { delete d; d = nullptr; }
	return true;
}

void SDLApplication::exitGame()
{
	while (!_myStateMachine.empty())
		_myStateMachine.popState();
}

void SDLApplication::exitPause()
{
	pauseExit = true;
}

void SDLApplication::replaceState(GameState* gS)
{
	_myStateMachine.replaceState(gS);
}

void SDLApplication::pushState(GameState* gS)
{
	_myStateMachine.pushState(gS);
}

void SDLApplication::run()
{
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();
	while (!_myStateMachine.empty()) {
		startTime = SDL_GetTicks();
		_myStateMachine.update();
		SDL_RenderClear(renderer);
		_myStateMachine.render();
		SDL_RenderPresent(renderer);
		SDL_Event event;
		if (SDL_PollEvent(&event)) {
			_myStateMachine.handleEvent(event);
		}
		if (playState) {
			PlayState* aux = new PlayState(this);
			replaceState(aux);
			playState = false;
		}
		if (pauseExit) {
			_myStateMachine.popState();
			pauseExit = false;
		}
		if (vuelvMenu) {
			MainMenuState* _mainMenu = new MainMenuState(this, textures[MAINMENUTEXTURE], textures[CONTINUAR],
				textures[CARGARPARTIDA], textures[SALIR]);
			replaceState(_mainMenu);
			vuelvMenu = false;
		}
		if (exit) {
			exitGame();
		}
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteraci�n
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}