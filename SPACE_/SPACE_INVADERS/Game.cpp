#include "Game.h"
#include <fstream>
#include <vector>

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

	if (!file.is_open()) throw "No se ha abierto el archivo.";

	const uint NUM_ALIENS = 100;
	const uint NUM_BUNKERS = 100;

	int tObject = -1;
	float x = 0, y = 0;
	float xMap = 0, yMap = 0;
	int alienType = -1;
	bool idle = false;
	uint nObjects = 0;
	uint row = 0, col = 0;
	vector <Alien*> aliens;
	vector <Bunker*> bunkers;

	//Lectura del cannon
	file >> tObject;
	file >> x;
	file >> y;
	Point2D<float> posCannon(x, y);
	cannon = new Cannon(posCannon, (uint)3, 2.0f, textures[CANNONTEXTURE], this, (uint)34, (uint)21);
	
	//Lectura del aliensMap
	file >> tObject;
	while (tObject == 1) {
		file >> x;
		file >> y;
		file >> alienType;
		if (col == 0 && row == 0) { //Coordenadas del inicio del aliensMap
			xMap = x;
			yMap = y;
		}
		Point2D<float> posAlien(x, y);
		Alien* aux = new Alien(posAlien, (uint)alienType, textures[ALIENSMAPTEXTURE], this, (uint)48, 
			(uint)32, row, col, idle);
		col++;
		idle = !idle;
		if (col == 11 && row < 4) {
			row++;
			col = 0;
			idle = false;
		}
		aliens.push_back(aux);
		nObjects++;
		file >> tObject;
		aux = nullptr;
	}
	Point2D<float> posAliensMap(xMap, yMap);
	aliensMap = new AliensMap(textures[ALIENSMAPTEXTURE], aliens, nObjects, (uint)48, (uint)32, (uint)96, (uint)96, row, 
		col, posAliensMap);
	
	nObjects = col = row = 0;
	//Lectura de bunkersMap
	while (!file.eof()) {
		file >> x;
		file >> y;
		if (col == 0 && row == 0) { //Coordenadas del inicio del aliensMap
			xMap = x;
			yMap = y;
		}
		Point2D<float> posBunker(x, y);
		Bunker* aux = new Bunker(posBunker, (uint)4, textures[BUNKERSMAPTEXTURE], (uint)90, (uint)59, row, col);
		++col;
		bunkers.push_back(aux);
		nObjects++;
		file >> tObject;
		aux = nullptr;
	}
	Point2D<float> posBunkersMap(xMap, yMap);
	bunkersMap = new BunkersMap(textures[BUNKERSMAPTEXTURE], bunkers, nObjects, (uint)4, (uint)90, (uint)59, 
		(uint)360, (uint)59, row, col, posBunkersMap);

	//Setteo del Background
	Point2D<float> posStar(0, 0);
	star = new Star(posStar, textures[STARTEXTURE], 800, 600);

	file.close();
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

void Game::render() const {
	SDL_RenderClear(renderer);
	star->render();
	cannon->render();
	aliensMap->render();
	bunkersMap->render();
	SDL_RenderPresent(renderer);
}

void Game::update() {
	cannon->update();
	aliensMap->update();
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();


	while (!gameover && !exit && !win) {
		startTime = SDL_GetTicks();
		//handleEvents(gameover, exit, win);
		update(); // Actualiza el estado de todos los objetos del juego
		render(); // Renderiza todos los objetos del juego
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteración
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}
