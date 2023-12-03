#include "Game.h"
#include <random>
#include <fstream>

Game::Game() {

	init();
	textureLoading();
	if (textureLoading())
		loadFromFile("../images/mapas/pred" + to_string(nLevel % nLevels) +".txt");
	else throw "No se cargaron corretamente las texturas.";
}

Game::~Game() {
	for (auto it : objectsList) {
		delete it;
		it = nullptr;
	}
	delete infoBar;
	for (Texture* t : textures) { delete t; t = nullptr; }
	delete mother;
	delete star;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
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
		throw SDL_GetError(); //exception("Error loading SDL window or renderer");
}

void Game::limpiaLista() {
	for (auto it : objectsList) {
		delete it;
		it = nullptr;
	}
	objectsList.clear();
}

void Game::loadFromFile(string fileName) {
	limpiaLista();
	if (infoBar != nullptr) {
		delete infoBar;
	}
	ifstream file(fileName); //Hay 50 elementos que leer
	int latestRow = -1, tObject, posX, posY, subType, nlifes, estado, points;
	bool idle = false;

	SceneObject* aux = nullptr; //Alamcena cada SceneObject 

	if (!file.is_open()) throw "No se ha abierto el archivo.";

	while (!file.eof()) {
		file >> tObject;
		file >> posX;
		file >> posY;
		Point2D<float> pos(posX, posY);

		switch (tObject) {
		case 0: //Cannon
			file >> nlifes;
			file >> estado; //TODO: que esto sea la espera

			aux = new Cannon(pos, textures[CANNONTEXTURE], pair<uint, uint>(34, 21), this, nlifes, estado, 30); //Instance
				_landedHeight = pos.getY() - 30;
				_cannon = static_cast<Cannon*>(aux);
			break;
		case 1: //Alien
			file >> subType;

			if (latestRow != posY) //Different Alien frame each column
			{
				idle = false;
				latestRow = posY;
			}
			else idle = !idle;

			aux = new Alien(pos, textures[ALIENSTEXTURE], pair<uint, uint>(48, 32), this, 4, subType, idle);
			static_cast<Alien*>(aux)->setMother(mother);
			mother->addAlien();
			break;
		case 2: //Shooter alien
			file >> subType;
			file >> estado;

			if (latestRow != posY)
			{
				idle = false;
				latestRow = posY;
			}
			else idle = !idle;
			aux = new ShooterAlien(pos, textures[ALIENSTEXTURE], pair<uint, uint>(48, 32), this, 4, subType,
				idle);
			static_cast<Alien*>(aux)->setMother(mother);
			mother->addAlien();
			break;
		case 3: //Mothership
			file >> subType;
			mother->setState(posX);
			mother->setLevel(posY);
			mother->setActualLevel(subType);

			break;
		case 4: //Bunkers
			file >> subType; //TODO: ENTENDER ESTO

			aux = new Bunker(pos, textures[BUNKERSTEXTURE], pair<uint, uint>(90, 59), this, 4);
			break;
		case 5: //Ufo
			file >> estado;
			file >> subType; //TODO: LA ESPERA

			aux = new Ufo(this, pos, textures[UFOTEXTURE], pair < uint, uint>(90,32),estado,subType);
			break;
		case 6:
			file >> subType;
			aux = new Laser(pos, Vector2D<float>(0, 5), pair<uint, uint>(5, 20), this, renderer,(Father) subType);
			break;
		case 7: //Points
			file >> points;
			//Crrar instancia InfoBar
			break;
		default:
			throw "Objeto no identificado.";
			break;
		}

		if (tObject != 3 && tObject != 7) { //Mothership and Ufo dont belong the listObject
			addToList(aux);
		}
	}
	//Background
	if(star == nullptr)
		star = new Star(Point2D<float>(0, 0), textures[STARTEXTURE], pair<uint, uint>(WIN_WIDTH, WIN_HEIGHT));
	infoBar = new InfoBar(this, textures[CANNONTEXTURE], Point2D<float>(20, WIN_HEIGHT - 50),
		pair<uint, uint>(34, 21), 0);
}

void Game::render() const 
{
	SDL_RenderClear(renderer);
	star->render();
	for (auto it : objectsList) 
	{
		if (it != nullptr)
			it->render();
	}
	infoBar->render();

	SDL_RenderPresent(renderer);
}

void Game::update() 
{
	for (auto it : objectsList)
	{
		it->update();
	}

	//Sumamos la puntuacion
	

	for (auto it : objectsToDelete) {
		delete *it;
		objectsList.erase(it);
	}

	if (!objectsToDelete.empty()) {
		objectsToDelete.clear();
	}

	mother->update();
}

void Game::save(int k) const{
	string direc = "../images/mapas/pred" + to_string(k);
	ofstream out(direc + ".txt");
	if (!out.is_open()) throw "No se ha abierto el archivo.";
	for (auto it : objectsList)
	{
		it->save(out); 
	}
	mother->save(out);
	out.close(); 
}


void Game::handleEvents() {
	int k;
	SDL_Event event;

	while (SDL_PollEvent(&event) && !exit) {
		if (event.key.keysym.sym == SDLK_ESCAPE) exit = true;
		else if (!pauseSave && !pauseCharge && event.key.keysym.sym == SDLK_s) pauseSave = true;
		else if (!pauseSave && !pauseCharge && event.key.keysym.sym == SDLK_l) pauseCharge = true;
		else if (pauseSave && event.key.keysym.sym == SDLK_0) { save(0); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_1) { save(1); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_2) { save(2); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_3) { save(3); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_4) { save(4); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_5) { save(5); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_6) { save(6); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_7) { save(7); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_8) { save(8); pauseSave = false; }
		else if (pauseSave && event.key.keysym.sym == SDLK_9) { save(9); pauseSave = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_0) { loadFromFile("../images/mapas/map0.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_1) { loadFromFile("../images/mapas/map1.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_2) { loadFromFile("../images/mapas/map2.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_3) { loadFromFile("../images/mapas/map3.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_4) { loadFromFile("../images/mapas/map4.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_5) { loadFromFile("../images/mapas/map5.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_6) { loadFromFile("../images/mapas/map6.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_7) { loadFromFile("../images/mapas/map7.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_8) { loadFromFile("../images/mapas/map8.txt"); pauseCharge = false; }
		else if (pauseCharge && event.key.keysym.sym == SDLK_9) { loadFromFile("../images/mapas/map9.txt"); pauseCharge = false; }
		else if(!pauseSave && !pauseCharge) _cannon->handleEvents(event, renderer);
	}
}

void Game::addToList(SceneObject* aux) {
	/*list<SceneObject*>::iterator i = objectsList.end();
	objectsList.insert(i, aux); //SceneObject to list
	i++;*/
	list<SceneObject*>::iterator i = objectsList.insert(objectsList.end(),aux);
	aux->setListIterator(i); //Set the iterator
}

bool Game::textureLoading(){
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
		textures.push_back(new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second));
	}
	for (TextureData* d : dataTextures) { delete d; d = nullptr; }
	return true;
}

void Game::lose() 
{
	gameOver = true;
}

void Game::Win() {
	nLevel++;
	string direc = "../images/mapas/pred" + to_string(nLevel % nLevels) + ".txt";
	loadFromFile(direc);
}

void Game::hasDie(list<SceneObject*>::iterator it) {
	objectsToDelete.push_back(it);
}

bool Game::damage(SDL_Rect rect, Father father) const {
	for (auto it : objectsList) {
		if (it->hit(rect, father))
			return true;
	}
	return false;
}

int Game::getRandomRange(int min, int max) {
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}
void Game::run() {
	uint32_t startTime, frameTime;
	startTime = SDL_GetTicks();

	while (!gameOver && !exit && !win)
	{
		startTime = SDL_GetTicks();
		handleEvents();
		if (!pauseCharge && !pauseSave) 
		{
			update(); // Actualiza el estado de todos los objetos del juego
		}
		render(); // Renderiza todos los objetos del juego
		frameTime = SDL_GetTicks() - startTime; // Tiempo de la iteraci?n
		if (frameTime < FRAME_RATE)
			SDL_Delay(FRAME_RATE - frameTime); // Suspende por el tiempo restante
	}
}