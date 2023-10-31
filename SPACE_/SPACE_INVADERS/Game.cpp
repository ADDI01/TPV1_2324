#include "Game.h"
#include <fstream>
#include <vector>

Game::Game() {

	init();

	texturePath[CANNONTEXTURE] = "../images/spaceship.png";
	texturePath[ALIENSMAPTEXTURE] = "../images/aliens.png";
	texturePath[BUNKERSMAPTEXTURE] = "../images/bunker.png";
	texturePath[STARTEXTURE] = "../images/stars.png";

	// We now create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
		if (i == ALIENSMAPTEXTURE) 
		{
			textures[i] = new Texture(renderer, texturePath[i], 3, 2);
		}
		else if (i == BUNKERSMAPTEXTURE) 
		{
			textures[i] = new Texture(renderer, texturePath[i], 1, 4);
		}
		else 
		{
			textures[i] = new Texture(renderer, texturePath[i], 1, 1);
		}
	}

	loadFromFile();
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
			(uint)32, row, col);
		col++;
		if (col == 11 && row < 4) {
			row++;
			col = 0;
		}
		aliens.push_back(aux);
		nObjects++;
		file >> tObject;
		delete aux;
	}
	Point2D<float> posAliensMap(xMap, yMap);
	aliensMap = new AliensMap(textures[ALIENSMAPTEXTURE], aliens, nObjects, 48, 32, 96, 96, row, col, 
		posAliensMap);
	
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
		Bunker* aux = new Bunker(posBunker, (uint)4, textures[BUNKERSMAPTEXTURE], row, col, (uint)90, (uint)59);
		++col;
		bunkers.push_back(aux);
		nObjects++;
		file >> tObject;
		delete aux;
	}
	Point2D<float> posBunkersMap(xMap, yMap);
	bunkersMap = new BunkersMap(textures[BUNKERSMAPTEXTURE], bunkers, nObjects, (uint)4, (uint)90, (uint)59, 
		(uint)360, (uint)59, row, col, posBunkersMap);

	//Setteo del Background
	Point2D<float> posStar(0, 0);
	star = new Star(posStar, textures[STARTEXTURE], 600, 450);

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
