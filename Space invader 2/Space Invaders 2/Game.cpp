#include "Game.h"
#include <random>
#include <fstream>

using namespace std;

Game::~Game() {
	for (auto it : objectsList) {
		delete it;
		it = nullptr;
	}
	delete infoBar;
	for (Texture* t : textures) { delete t; t = nullptr; }
	delete _mother;
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
	if (window == nullptr || renderer == nullptr) {
		throw SDLError("Error loading SDL window or renderer");
	}

	if (textureLoading())
		loadFromFile("../images/mapas/map" + to_string(nLevel % nLevels) + ".txt");
	else {
		throw SDLError("No se cargaron las texturas.");
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
		textures.push_back(new Texture(renderer, dataTextures[i]->texturePath, dataTextures[i]->dimensiones.first, dataTextures[i]->dimensiones.second));
	}
	for (TextureData* d : dataTextures) { delete d; d = nullptr; }
	return true;
}

void Game::loadFromFile(string fileName) { //TODO: Distribuir el load en las clases de los SceneObjects
	ifstream file(fileName); //Hay 50 elementos que leer
	SceneObject* aux = nullptr; //Stores every SceneObject 
	int tObject = -1, latestRow = -1, state = -1, level = -1, currentLvl = -1, points = -1;
	bool idle = false;
	
	limpiaLista();
	if (infoBar != nullptr) delete infoBar;
	if (!file.is_open()) throw FileNotFoundError(fileName);

	//Specific objects are created here
	_mother = new Mothership(this, 0, 0, MOTHERSHIP_MOV_CD);
	star = new Star(Point2D<float>(0, 0), textures[STARTEXTURE], pair<uint, uint>(WIN_WIDTH, WIN_HEIGHT));
	
	while (!file.eof()) {
		file >> tObject;

		switch (tObject) { 
		case 0: //Cannon
			_cannon = new Cannon(this, file, textures[CANNONTEXTURE], CANNON_SPEED);
			aux = _cannon;
			break;
		case 1: //Alien
			_alien = new Alien(this, file, textures[ALIENSTEXTURE], ALIEN_SPEED, latestRow);
			_alien->setMother(_mother);
			_mother->addAlien();
			aux = _alien;
			_alien = nullptr;
			break;
		case 2: //Shooter alien
			_shooterAlien = new ShooterAlien(this, file, textures[ALIENSTEXTURE], ALIEN_SPEED, latestRow);
			_shooterAlien->setMother(_mother);
			_mother->addAlien();
			aux = _shooterAlien;
			_shooterAlien = nullptr;
			break;
		case 3: //Mothership
			file >> state;
			file >> level;
			file >> currentLvl;
			_mother->setState(state);
			_mother->setLevel(level);
			_mother->setActualLevel(currentLvl);
			break;
		case 4: //Bunkers
			_bunker = new Bunker(this, file, textures[BUNKERSTEXTURE]);
			aux = _bunker;
			_bunker = nullptr;
			break;
		case 5: //Ufo
			_ufo = new Ufo(this, file, textures[UFOTEXTURE]);
			aux = _ufo;
			_ufo = nullptr;
			break;
		case 6:
			_laser = new Laser(this, renderer, file, LASER_SIZE, LASER_SPEED);
			aux = _laser;
			_laser = nullptr;
			break;
		case 7: //Points
			file >> points;
			infoBar = new InfoBar(this, textures[CANNONTEXTURE], INFOBAR_POS, INFOBAR_SIZE, points);
			break;
		default:
			throw FileFormatError(fileName);
			break;
		}

		if (tObject != 3 && tObject != 7) { //Mothership and Ufo dont belong the listObject
			addToList(aux);
		}
	}

	//Default InfoBar
	if(infoBar == nullptr) infoBar = new InfoBar(this, textures[CANNONTEXTURE], INFOBAR_POS, INFOBAR_SIZE, 0);
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

void Game::render() const
{
	SDL_RenderClear(renderer);
	star->render();
	for (auto it : objectsList)
	{
		it->render();
	}
	infoBar->render();
	SDL_RenderPresent(renderer);
}

void Game::update()
{
	//int aux = 1;
	for (auto it : objectsList)
	{
		//if(typeid(*it) == typeid(Laser))
			//cout << "Laser " << aux << " " << it->getPos().getX() << " " << it->getPos().getY() << std::endl;
		it->update();
	}
	//aux = 0;

	for (auto it : objectsToDelete) {
		if (typeid(*it.operator*()) == typeid(Laser)) {
			std::cout << "Laser " << it.operator*()->getPos().getX() << " "
				<< it.operator*()->getPos().getY() << std::endl;
			static_cast<Laser*>(*it)->setAux(1);
		}
			
		delete* it; //Delete the content of the pointer
		objectsList.erase(it); //Free the pointer
	}

	if (!objectsToDelete.empty())
		std:cout << "Delete elems " << objectsToDelete.size() << std::endl;

	if (!objectsToDelete.empty()) {
		objectsToDelete.clear();
	}
	_mother->update();
}

void Game::save(int k) const{
	string direc = "../images/mapas/pred" + to_string(k);
	ofstream out(direc + ".txt");
	if (!out.is_open()) {
		throw FileFormatError(direc);
	}
	for (auto it : objectsList)
	{
		it->save(out); 
	}
	_mother->save(out);
	out.close(); 
}

void Game::handleEvents() {
	int k;
	SDL_Event event;
	// se pueden leer directamente los números
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

void Game::lose() 
{
	gameOver = true;
}

void Game::gameWin() {
	nLevel++;
	string direc = "../images/mapas/pred" + to_string(nLevel % nLevels) + ".txt";
	loadFromFile(direc);
};

void Game::addToList(SceneObject* aux) {
	/*list<SceneObject*>::iterator i = objectsList.end();
	objectsList.insert(i, aux); //SceneObject to list
	i++;*/
	list<SceneObject*>::iterator i = objectsList.insert(objectsList.end(), aux);
	aux->setListIterator(i); //Set the iterator
}

bool Game::damage(SDL_Rect rect, Father father) const {
	for (auto it : objectsList) {
		if (it->hit(rect, father))
			return true;
	}
	return false;
}

void Game::hasDie(list<SceneObject*>::iterator it) {
	objectsToDelete.push_back(it);
	if(it.operator*()->getPos().getY() >= 600)
		std::cout << "1" << std::endl;
}

void Game::limpiaLista() {
	for (auto it : objectsList) {
		delete it;
		it = nullptr;
	}
	objectsList.clear();
}

int Game::getRandomRange(int min, int max) {
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}
