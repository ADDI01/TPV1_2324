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

Game::~Game() {

	for (Alien* a : aliens) { delete a; a = nullptr; }
	for (Bunker* b : bunkers) { delete b; b = nullptr; }
	for (Laser* l : lasers) { delete l; l = nullptr; }
	for (Texture* t : textures) { delete t; t = nullptr; }
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete cannon;
	delete star;
	SDL_Quit();
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

bool Game::textureLoading() {

	texturePath[CANNONTEXTURE] = "../images/spaceship.png";
	texturePath[ALIENSMAPTEXTURE] = "../images/aliens.png";
	texturePath[BUNKERSMAPTEXTURE] = "../images/bunker.png";
	texturePath[STARTEXTURE] = "../images/stars.png";

	//Now, we create the textures
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
	ifstream file("../images/mapas/trinchera.txt");
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

			aliens.push_back(alienaux);

			alienaux = nullptr;
			break;
		case 2: //Bunkers
			bunkeraux = new Bunker(pos, textures[BUNKERSMAPTEXTURE], tGameObjsProps.bunkerW, tGameObjsProps.bunkerH,
				tGameObjsProps.bunkerLifes);

			bunkers.push_back(bunkeraux);

			bunkeraux = nullptr;
			break;
		default:
			throw "Objeto no identificado.";
		}
	}

	//Setteo del Background
	Point2D<float> pos(0, 0);
	star = new Star(pos, textures[STARTEXTURE], WIN_WIDTH, WIN_HEIGHT);

	file.close();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();


	while (!gameOver && !exit && !win) {
		startTime = SDL_GetTicks();
		handleEvents();
		update(); // Actualiza el estado de todos los objetos del juego
		render(); // Renderiza todos los objetos del juego
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteraci�n
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}

void Game::render() const {
	SDL_RenderClear(renderer);
	star->render();
	cannon->render();
	for (Bunker* e : bunkers)
	{
		e->render();
	}

	for (Alien* e : aliens)
	{
		e->render();
	}

	for (Laser* l : lasers)
	{
		l->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::update() {

	//Collisions Alien - Bunker and Alien - Cannon
	onHitAlien();

	//Collisions Player's laser - Alien
	onHitPlayerLasertoAlien();

	//Collisions Alien's laser - Bunker and Alien's laser - Cannon
	onHitAlienLaser();

	//Alien's update. Delete of dead aliens if update is false
	aliensUpdate();

	//Laser's update. Delete of lasers that has hit something if update is false
	lasersUpdate();

	//Bunker's update. Delete of bunkers with no lifes left if update is false
	bunkersUpdate();

	//Change alien's direction when they hit the side of the screen
	if (tGameObjsProps.alienCannotMove)
	{
		for (Alien* e : aliens)
		{
			e->bajaColumna();
		}
		tGameObjsProps.alienDirection *= -1;
		tGameObjsProps.alienCannotMove = false;
	}

	//End conditions
	if (!cannon->update())
	{
		gameOver = true;
	}
	if (aliens.empty())
	{
		win = true;
	}
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit) {
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

			if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (cannon->canShoot())
				{
 					Laser* laseraux = new Laser(cannon->getPosition() - Vector2D<float>(0, tGameObjsProps.cannonH), 
						tGameObjsProps.laserVelocity, 1, this, renderer, tGameObjsProps.laserW, tGameObjsProps.laserH);
					lasers.push_back(laseraux);
					cannon->setCoolDown(tGameObjsProps.cannonshootCD);
				}
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				exit = true;
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

void Game::lose() {

	gameOver = true;
}

void Game::aliensUpdate() {

	for (int i = 0; i < aliens.size(); i++)
	{
		if (!aliens[i]->update())
		{
			delete aliens[i];
			aliens[i] = nullptr;
			aliens.erase(aliens.begin() + i);
		}
	}
}

void Game::lasersUpdate() {

	for (int i = 0; i < lasers.size(); i++)
	{
		if (!lasers[i]->update())
		{
			delete lasers[i];
			lasers[i] = nullptr;
			lasers.erase(lasers.begin() + i);
		}
	}
}

void Game::bunkersUpdate() {

	for (int i = 0; i < bunkers.size(); i++)
	{
		if (!bunkers[i]->update())
		{
			delete bunkers[i];
			bunkers[i] = nullptr;
			bunkers.erase(bunkers.begin() + i);
		}
	}
}

void Game::onHitPlayerLasertoAlien() {

	for (int i = 0; i < lasers.size(); i++)
	{
		if (lasers[i]->getFather() == 1) 
		{
			//Collisions Player's laser - Alien
			for (int j = 0; j < aliens.size(); j++)
			{
				if (SDL_HasIntersection(lasers[i]->getRect(), aliens[j]->getRect()))
				{
					lasers[i]->hit();
					aliens[j]->hit();
				}
			}
		}
		
	}
}

void Game::onHitAlienLaser() {

	for (int i = 0; i < lasers.size(); i++)
	{
		if (lasers[i]->getFather() == 0) 
		{
			//Collisions Alien's laser - Bunker
			for (int j = 0; j < bunkers.size(); j++)
			{
				if (SDL_HasIntersection(lasers[i]->getRect(), bunkers[j]->getRect()))
				{
					lasers[i]->hit();
					bunkers[j]->hit();
				}
			}

			//Collisions Alien's laser - Cannon
			if (SDL_HasIntersection(lasers[i]->getRect(), cannon->getRect()))
			{
				cannon->hit();
				lasers[i]->hit();
			}
		}
	}
}
void Game::onHitAlien() {
	bool hasHit = false;

	for (int i = 0; i < aliens.size(); i++)
	{
		//Collisions Alien - Bunker
		for (int j = 0; j < bunkers.size(); j++)
		{
			if (SDL_HasIntersection(aliens[i]->getRect(), bunkers[j]->getRect()))
			{
				aliens[i]->hit();
				bunkers[j]->hit();
				hasHit = true;
			}
		}
		
		//Collisions Alien - Cannon
		if (!hasHit && SDL_HasIntersection(aliens[i]->getRect(), cannon->getRect()))
		{
			cannon->hit();
			aliens[i]->hit();
		}
	}
}

int Game::getRandomRange(int min, int max) {
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void Game::cannotMove() {
	tGameObjsProps.alienCannotMove = true;
}

void Game::fireLaser(Alien* alien) {
	Laser* laseraux = new Laser(alien->getPosition() + Vector2D<float>(0, tGameObjsProps.alienH/3), 
		tGameObjsProps.laserVelocity, 0, this, renderer, tGameObjsProps.laserW, tGameObjsProps.laserH);
	lasers.push_back(laseraux);
}