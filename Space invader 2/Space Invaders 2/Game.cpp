#include "Game.h"
#include <random>

Game::Game() {

	init();
	textureLoading();

	mother = new Mothership(this);
	alien = new Alien(Point2D<float>(50, 50), textures[ALIENSTEXTURE],pair<uint, uint>( 48, 32), this,mother, 1, 1,false);
	bunker = new Bunker(Point2D<float>(300, 300), textures[BUNKERSTEXTURE], pair<uint, uint>(90, 59), this, 4);
	cannon = new Cannon(Point2D<float>(400, 400), textures[CANNONTEXTURE], pair<uint, uint>(34, 21), this, 3, 30, 1);
	laser = new Laser(Point2D<float>(20, 100), Vector2D<float>(0, 10), pair<uint, uint>(5, 10), this, renderer, PLAYER);
	//if (textureLoading())
		//loadFromFile();
	//else throw "No se cargaron corretamente las texturas.";
}


void Game::init() {
	// We first initialize SDL
	// Inicializar SDL, crear ventana y renderizador
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw exception("Error loading SDL window or renderer");
}

void Game::render() const 
{
	SDL_RenderClear(renderer);
	alien->render();
	bunker->render();
	cannon->render();
	laser->render();
	SDL_RenderPresent(renderer);
}

void Game::update() 
{
	alien->update();
}

bool Game::textureLoading() {
	// cannon's texture inicialization
	//dataTextures[CANNONTEXTURE]->texturePath = "../images/spaceship.png";
	//dataTextures[CANNONTEXTURE]->dimensiones = pair<uint, uint>(1, 1);
	dataTextures[CANNONTEXTURE] = new TextureData("../images/spaceship.png", pair<uint, uint>(1, 1));

	//alien's texture inicialization
	//dataTextures[ALIENSTEXTURE]->texturePath = "../images/aliens.png";
	//dataTextures[ALIENSTEXTURE]->dimensiones = pair<uint, uint>(3, 2);
	dataTextures[ALIENSTEXTURE] = new TextureData("../images/aliens.png", pair<uint, uint>(3, 2));

	//bunker's texture inicialization
	//dataTextures[BUNKERSTEXTURE]->texturePath = "../images/bunker.png";
	//dataTextures[BUNKERSTEXTURE]->dimensiones = pair<uint, uint>(1, 4);
	dataTextures[BUNKERSTEXTURE] = new TextureData("../images/bunker.png", pair<uint, uint>(1, 4));


	//bunker's texture inicialization
	//dataTextures[STARTEXTURE]->texturePath = "../images/stars.png";
	//dataTextures[STARTEXTURE]->dimensiones = pair<uint, uint>(1, 1);
	dataTextures[STARTEXTURE] = new TextureData("../images/stars.png", pair<uint, uint>(1, 1));

	//Ufo's texture
	//dataTextures[UFOTEXTURE] = new TextureData()

	//Now, we create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		if (i == ALIENSTEXTURE)
		{
			textures[i] = new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first,
				dataTextures[i]->dimensiones.second);
		}
		else if (i == BUNKERSTEXTURE)
		{
			textures[i] = new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second);
		}
		else if (i == CANNONTEXTURE || i == STARTEXTURE)
		{
			textures[i] = new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second);
		}
		else return false;
	}
	return true;
}

void Game::lose() 
{
	gameOver = true;
}

int Game::getRandomRange(int min, int max) {
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();


	while (!gameOver /*&& !exit && !win */)
	{
		startTime = SDL_GetTicks();
		//handleEvents();
		update(); // Actualiza el estado de todos los objetos del juego
		render(); // Renderiza todos los objetos del juego
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteraci?n
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}