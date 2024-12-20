#include "PlayState.h"
#include "PauseState.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "EndState.h"
#include <fstream>
#include <string>
#include <random>
using namespace std;
PlayState::~PlayState()
{
	gameList.clear();
	//delete infoBar;
	delete _mother;
	//delete star;
}

bool PlayState::mayGrantReward( SDL_Rect& rect) //Cambiar por return metodo
{
	return SDL_HasIntersection(&rect, _cannon->getRect());
}

void PlayState::render() const
{
	//star->render();
	for (auto it = gameList.begin(); it != gameList.end(); ++it)
	{
		(*it).render();
	}
	//infoBar->render();
}

void PlayState::update()
{
	infoBar->update();
	_mother->update();
	for (auto it = gameList.begin(); it != gameList.end(); ++it) {
		(*it).update();
	}
	if (win) {
		gameWin();
		win = false;
	}
	if (losed) {
		EndState* end = new EndState(myGame, myGame->getTexture()[VOLVERALMENU], myGame->getTexture()[SALIR]);
		myGame->replaceState(end);

	}
}


void PlayState::handleEvent(const SDL_Event& event) {
	if (event.key.keysym.sym == SDLK_ESCAPE)
	{
		PauseState* pause = new PauseState(myGame, myGame->getTexture()[CONTINUAR], myGame->getTexture()[GUARDARPARTIDA],
			myGame->getTexture()[CARGARPARTIDA], myGame->getTexture()[SALIR]);
		myGame->pushState(pause);
		pause->setPlayState(this);
	}

	for (EventHandler* it : eventHandlerList) {
		it->manageEvent(event);
	}
}

bool PlayState::damage(SDL_Rect rect, Father father) const
{
	for (auto it = _sceneObjectList.begin(); it != _sceneObjectList.end(); ++it) {
		if ((*it).hit(rect, father))
			return true;
	}
	return false;
}

void PlayState::HasDied(GameList<SceneObject,false>::anchor itS)
{
	GameState::HasDied(itS->elem->getListAnchor());
	_sceneObjectList.erase(itS);
}

void PlayState::limpiaLista()
{
	gameList.clear();
	_sceneObjectList.clear();
	eventHandlerList.clear();
}

void PlayState::gameWin()
{
	nLevel++;
	string direc = "./recursos/mapas/pred" + to_string(nLevel % nLevels) + ".txt";
	loadFromFile(direc);
}

void PlayState::save(std::string file)
{
	ofstream out(file);
	if (!out.is_open()) {
		throw FileFormatError(file);
	}
	for (auto it = gameList.begin(); it != gameList.end(); ++it)
	{
		(*it).save(out);
	}
	_mother->save(out);
	infoBar->save(out);
	out.close();
}

void PlayState::escudo()
{
	_cannon->setInvincibility(true);
}

void PlayState::loadFromFile(std::string fileName)
{
	//TODO: Distribuir el load en las clases de los SceneObjects
	ifstream file(fileName); //Hay 50 elementos que leer 
	SceneObject* aux = nullptr; //Stores every SceneObject 
	EventHandler* e = nullptr;
	int tObject = -1, latestRow = -1, state = -1, level = -1, currentLvl = -1, points = -1;
	bool idle = false;

	limpiaLista();
	//if (infoBar != nullptr) delete infoBar;
	if (!file.is_open()) throw FileNotFoundError(fileName);

	//Specific objects are created here
	//if(star == nullptr)
	star = new Star(this, Point2D<float>(0, 0), myGame->getTexture()[STARTEXTURE], pair<uint, uint>(WIN_WIDTH, WIN_HEIGHT));
	addObject(star);
	if (_mother != nullptr)
		delete _mother;
	_mother = new Mothership(this,this, 0, MOTHERSHIP_LEVEL, MOTHERSHIP_MOV_CD);
	infoBar = new InfoBar(this, myGame->getRenderer(), this, myGame->getTexture()[CANNONTEXTURE], INFOBAR_POS, INFOBAR_SIZE, 0, FONT_SIZE);
	addObject(infoBar);

	while (!file.eof()) {
		file >> tObject;

		switch (tObject) {
		case 0: //Cannon
			_cannon = new Cannon(this, this, myGame, file, myGame->getTexture()[CANNONTEXTURE], CANNON_SPEED);
			aux = _cannon;
			e = _cannon;
			addEventListener(e);
			break;
		case 1: //Alien
			_alien = new Alien(this, this, myGame, file, myGame->getTexture()[ALIENSTEXTURE], ALIEN_SPEED, latestRow);
			_alien->setMother(_mother);
			_mother->addAlien();
			aux = _alien;
			_alien = nullptr;
			break;
		case 2: //Shooter alien
			_shooterAlien = new ShooterAlien(this, this,myGame, file, myGame->getTexture()[ALIENSTEXTURE], ALIEN_SPEED, latestRow);
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
			_bunker = new Bunker(this, this, myGame, file, myGame->getTexture()[BUNKERSTEXTURE]);
			aux = _bunker;
			_bunker = nullptr;
			break;
		case 5: //Ufo
			_ufo = new Ufo(this, this, myGame, file, myGame->getTexture()[UFOTEXTURE]);
			aux = _ufo;
			_ufo = nullptr;
			break;
		case 6:
			_laser = new Laser(this, this, myGame, myGame->getRenderer(), file, LASER_SIZE, LASER_SPEED);
			aux = _laser;
			_laser = nullptr;
			break;
		case 7: //Points
			file >> points;
			infoBar->setInitPoints(points);
			break;
		default:
			throw FileFormatError(fileName);
			break;
		}

		if (tObject != 3 && tObject != 7) { //Mothership and Ufo dont belong the listObject
			addSceneObject(aux);
			addObject(aux);
		}
	}
}

int PlayState::getRandomRange(int min, int max) {
	static std::mt19937_64 randomGenerator(std::random_device{}());
	return std::uniform_int_distribution<int>(min, max)(randomGenerator); 
}
