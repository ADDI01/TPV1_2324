#include "Game.h"
#include <random>
#include <fstream>

Game::Game() {

	init();
	textureLoading();
	if (textureLoading())
		loadFromFile();
	else throw "No se cargaron corretamente las texturas.";
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


void Game::loadFromFile() {
	ifstream file("../images/mapas/original.txt");
	uint latestRow = -1;
	int tObject, posX, posY, subType,nlifes, estado;
	bool idle;

	if (!file.is_open()) throw "No se ha abierto el archivo.";

	while (!file.eof()) {
		file >> tObject;
		file >> posX;
		file >> posY;
		Point2D<float> pos(posX, posY);

		SceneObject* aux = nullptr;;
		auto i = objectsList.end();

		switch (tObject) {
		case 0: //Cannon
			file >> nlifes;
			file >> subType; //TODO: que esto sea la espera

			aux = new Cannon(pos, textures[CANNONTEXTURE], pair<uint, uint>(34, 21), this, nlifes, 2, 1); //Instance
			objectsList.insert(i, aux); //SceneObject to list
			static_cast<SceneObject*>(*i)->setListIterator(i);
			break;
		case 1: //Aliens
			file >> subType;

			if (latestRow != posY)
			{
				idle = false;
				latestRow = posY;
			}
			else idle = !idle;
			aux = new ShooterAlien(pos, textures[ALIENSTEXTURE], pair<uint, uint>(48, 32), this, 4,
				subType, idle);
			static_cast<Alien*>(aux)->setMother(mother);
			objectsList.insert(objectsList.end(), aux);
			mother->addAlien();
			break;

		case 2:
			file >> subType;
			file >> nlifes;
			if (latestRow != posY)
			{
				idle = false;
				latestRow = posY;
			}
			else idle = !idle;
			aux = new Alien(pos, textures[ALIENSTEXTURE], pair<uint, uint>(48, 32), this, 4,
				subType, idle);
			static_cast<Alien*>(aux)->setMother(mother);
			objectsList.insert(objectsList.end(), aux);
			break;
			mother->addAlien();

		case 3:
			// leer nave
			objectsList.insert(objectsList.end(), aux);
			for (auto it : objectsList)
			{
				if (static_cast<Alien*>(it) != nullptr)
					static_cast<Alien*>(aux)->setMother(mother);
			}
			break;
		case 4: //Bunkers
			file >> subType; //TO:DO ENTENDER ESTO
			aux = new Bunker(pos, textures[BUNKERSTEXTURE], pair<uint, uint>(90, 59), this,
				4);

			objectsList.insert(objectsList.end(), aux);
			break;
		case 5:
			file >> estado;
			file >> subType; //TO:DO LA ESPERA
			aux = new Ufo(this, pos, textures[UFOTEXTURE], pair < uint, uint>(90,32));
			objectsList.insert(objectsList.end(), aux);
			break;
		default:
			//throw "Objeto no identificado.";
			break;
		}


	}

	star = new Star(Point2D<float>(0, 0), textures[STARTEXTURE], WIN_WIDTH, WIN_HEIGHT);
}

void Game::render() const 
{
	SDL_RenderClear(renderer);
	star->render();
	for (auto it : objectsList) 
	{
		if(static_cast<Cannon*>(it) != nullptr)
		static_cast<Cannon*>(it)->render();
		else if(static_cast<Bunker*>(it) != nullptr)
			static_cast<Bunker*>(it)->render();
		else if (static_cast<Alien*>(it) != nullptr)
			static_cast<Alien*>(it)->render();
		else if (static_cast<Ufo*>(it) != nullptr)
			static_cast<Ufo*>(it)->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::update() 
{
	for (auto it : objectsList)
	{
		if (static_cast<Cannon*>(it) != nullptr)
			static_cast<Cannon*>(it)->update();
		else if (static_cast<Bunker*>(it) != nullptr)
			static_cast<Bunker*>(it)->update();
		else if (static_cast<Alien*>(it) != nullptr)
			static_cast<Alien*>(it)->update();
		else if (static_cast<Ufo*>(it) != nullptr)
			static_cast<Ufo*>(it)->update();
	}

	if (!mother->shouldMove()) 
	{
		for (auto it : objectsList)
		{
			if (dynamic_cast<Alien*>(it) != nullptr)
				dynamic_cast<Alien*>(it)->bajaColumna();
		}
		mother->changeDirection();
		mother->canMove();
	}
}

void Game::handleEvents() {
	SDL_Event event;
	list<SceneObject*>::iterator i = objectsList.begin();
	while (SDL_PollEvent(&event) && !exit) {
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
		   	exit = true;
		}
		else {
			dynamic_cast<Cannon*>(*i)->handleEvents(event);
		}
	}
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
	dataTextures[UFOTEXTURE] = new TextureData("../images/ufo.png", pair<uint, uint>(1, 2));

	//Now, we create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++) {
			textures[i] = new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second);
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

void Game::fireLaser(SceneObject* object) {
	Laser* laseraux = nullptr;
	if ((typeid(object) == typeid(Alien))) {
		laseraux = new Laser(dynamic_cast<Alien*>(object)->getPosition() 
			+ Vector2D<float>(0, dynamic_cast<Alien*>(object)->getRect()->w / 3),
			Vector2D<float>(0, 10), pair<uint, uint>(5, 10), this, renderer, ALIEN);
	}
	else if (typeid(object) == typeid(Cannon)) {
		laseraux = new Laser(dynamic_cast<Cannon*>(object)->getPosition()
			- Vector2D<float>(0, dynamic_cast<Cannon*>(object)->getRect()->w / 3),
			Vector2D<float>(0, 10), pair<uint, uint>(5, 10), this, renderer, ALIEN);
	}
	
	objectsList.insert(objectsList.end(), laseraux);
}

void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();


	while (!gameOver /*&& !exit && !win */)
	{
		startTime = SDL_GetTicks();
		handleEvents();
		update(); // Actualiza el estado de todos los objetos del juego
		render(); // Renderiza todos los objetos del juego
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteraci?n
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}