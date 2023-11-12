#include "Game.h"
#include <fstream>
#include <vector>
#include <random>

Game::Game() {

	init();

	if (textureLoading())
		loadFromFile();
	else throw "No se cargaron corretamente las texturas.";
}

bool Game::textureLoading() {

	texturePath[CANNONTEXTURE] = "../images/spaceship.png";
	texturePath[ALIENSMAPTEXTURE] = "../images/aliens.png";
	texturePath[BUNKERSMAPTEXTURE] = "../images/bunker.png";
	texturePath[STARTEXTURE] = "../images/stars.png";

	// Now we create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		if (i == ALIENSMAPTEXTURE)
		{
			textures[i] = new Texture(renderer, texturePath[i], 3, 2);
		}
		else if (i == BUNKERSMAPTEXTURE)
		{
			textures[i] = new Texture(renderer, texturePath[i], 1, 4);
		}
		else if (i == CANNONTEXTURE || i == STARTEXTURE)
		{
			textures[i] = new Texture(renderer, texturePath[i], 1, 1);
		}
		else return false;
	}
	return true;
}

void Game::loadFromFile() {
	ifstream file("../images/mapas/original.txt");
	uint latestRow = -1;
	Alien* alienaux = nullptr;
	Bunker* bunkeraux = nullptr;

	if (!file.is_open()) throw "No se ha abierto el archivo.";

	while (!file.eof()) {
		file >> tGameObjsProps.tObject;
		file >> tGameObjsProps.posX;
		file >> tGameObjsProps.posY;
		Point2D<float> pos(tGameObjsProps.posX, tGameObjsProps.posY);

		switch (tGameObjsProps.tObject) {
		case 0: //Cannon
			cannon = new Cannon(pos, textures[CANNONTEXTURE], tGameObjsProps.cannonW, tGameObjsProps.cannonH, this,
				tGameObjsProps.cannonLifes, tGameObjsProps.shootCD, tGameObjsProps.cannonVelocity);
			break;
		case 1: //Aliens
			file >> tGameObjsProps.subType;

			if (latestRow != tGameObjsProps.posY)
			{
				tGameObjsProps.idle = false;
				latestRow = tGameObjsProps.posY;
			}
			else tGameObjsProps.idle = !tGameObjsProps.idle;
			alienaux = new Alien(pos, textures[ALIENSMAPTEXTURE], tGameObjsProps.alienW, tGameObjsProps.alienH, this, tGameObjsProps.alienVelocity,
				tGameObjsProps.subType, tGameObjsProps.idle);
			
			tGameObjsProps.aliens.push_back(alienaux);

			alienaux = nullptr;
			break;
		case 2: //Bunkers
			bunkeraux = new Bunker(pos, textures[BUNKERSMAPTEXTURE], tGameObjsProps.bunkerW, tGameObjsProps.bunkerH,
				tGameObjsProps.bunkerLifes);

			tGameObjsProps.bunkers.push_back(bunkeraux);

			bunkeraux = nullptr;
			break;
		default:
			throw "Objeto no identificado.";
		}
	}
	//Setteo del Background
	Point2D<float> posStar(0, 0);
	star = new Star(posStar, textures[STARTEXTURE], 800, 600);
	file.close();
}

int Game::getRandomRange(int min, int max) 
{
	mt19937_64 randomGenerator(time(nullptr));
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

Vector2D<float> Game::getDirection() 
{
	return Vector2D<float> (tGameObjsProps.alienDirection,0);
}

void Game::cannotMove() 
{
	tGameObjsProps.alienCannotMove = true;
}

void Game::init() 
{
	// We first initialize SDL
	// Inicializar SDL, crear ventana y renderizador
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		throw exception("Error loading SDL window or renderer");
}

void Game::render() const {
	SDL_RenderClear(renderer);
	star->render();
	cannon->render();
	for (Bunker* e : tGameObjsProps.bunkers)
	{
		e->render();
	}

	for (Alien* e : tGameObjsProps.aliens)
	{
		e->render();
	}
	SDL_RenderPresent(renderer);
}

void Game::update() {
	cannon->update();

	for (Alien* a : tGameObjsProps.aliens) 
	{
		if (!a->update()) 
		{
			delete a;
			a = nullptr;
		}
	}

	if (tGameObjsProps.alienCannotMove) 
	{
		for (Alien* e : tGameObjsProps.aliens)
		{
			e->bajaColumna();
		}
		tGameObjsProps.alienDirection *= -1;
		tGameObjsProps.alienCannotMove = false;
	}
}

void Game::handleEvents() 
{
	SDL_Event event;
	bool exit = false;
	while (SDL_PollEvent(&event) && !exit) {

		if (event.type == SDL_QUIT)
			exit = true;
		switch (event.type)
		{
		case SDL_KEYDOWN:

			if (event.key.keysym.sym == SDLK_LEFT)
			{
				Vector2D<float> dir(-1, 0);
				cannon->handleEvents(dir);
			}
			else if (event.key.keysym.sym == SDLK_RIGHT)
			{
				Vector2D<float> dir(1, 0);
				cannon->handleEvents(dir);
			}
			else if (event.key.keysym.sym == SDLK_SPACE) 
			{
				
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
			{
				Vector2D<float> dir(0, 0);
				cannon->handleEvents(dir);
			}
			break;
		}
	}
}


void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();


	while (!gameover && !exit && !win) {
		startTime = SDL_GetTicks();
		handleEvents();
		update(); // Actualiza el estado de todos los objetos del juego
		render(); // Renderiza todos los objetos del juego
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteraci�n
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}