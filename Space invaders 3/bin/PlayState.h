#pragma once
#include "GameState.h"
#include "Cannon.h"
#include "Star.h"
#include "Bunker.h"
#include "Alien.h"
#include "InfoBar.h"
#include "ShooterAlien.h"
#include "Ufo.h"
#include "SDLApplication.h"

class SceneObject;
using uint = unsigned int;

class PlayState : public GameState
{
private:
	//SceneObject's pointers
	Mothership* _mother = new Mothership(this,this,0,20,2);
	Cannon* _cannon = new Cannon(Point2D<float>(400, 500), myGame->getTexture()[1], std::pair<uint, uint>(34, 21), this, this,myGame, 3, 20,30);
	Bunker* _bunker = new Bunker(Point2D<float>(300, 500), myGame->getTexture()[3], std::pair<uint, uint>(90, 59), this, this, myGame,1);
	Alien* _alien = new Alien(Point2D<float>(100, 100), myGame->getTexture()[2], std::pair<uint, uint>(48, 32), this, this, myGame, 10,2,true);
	ShooterAlien* _shooterAlien = new ShooterAlien(Point2D<float>(100, 100), myGame->getTexture()[2], std::pair<uint, uint>(48, 32),
		this, this, myGame, 10, 0, true); 
	Ufo* _ufo = new Ufo(this,this,myGame, Point2D<float>(800, 100), myGame->getTexture()[5], std::pair<uint, uint>(57, 32),0,10);
	//Laser* _laser = nullptr;
	Star* star = new Star(Point2D<float>(0, 0), myGame->getTexture()[4], std::pair<uint, uint>(800, 600));
	InfoBar* infoBar = new InfoBar(this, myGame->getRenderer(), this, myGame->getTexture()[1], Point2D<float>(10, WIN_HEIGHT - 30), 
		std::pair<uint, uint>(34, 21), 0, FONT_SIZE);

	//SceneObjects constants
	const uint FONT_SIZE = 50;
	const uint CANNON_SPEED = 30;
	const uint ALIEN_SPEED = 4;
	const Vector2D<float> LASER_SPEED = Vector2D<float>(0, 5);
	std::pair<uint, uint> LASER_SIZE = std::pair<uint, uint>(5, 20);
	const Point2D<float> INFOBAR_POS = Point2D<float>(10, WIN_HEIGHT - 30);
	std::pair<uint, uint> INFOBAR_SIZE = std::pair<uint, uint>(34, 21);
	const uint MOTHERSHIP_MOV_CD = 20;
	
	//condiciones del juego
	bool win = false;
	bool losed = false;
	float LandedHeight = 200;

	GameList<SceneObject, false> _sceneObjectList;
public:
	//has die, colisiones, etc.
	PlayState(SDLApplication* myGame) : GameState(myGame) {
		addObject(_cannon); addEventListener(_cannon); addObject(_bunker); addObject(_alien); _alien->setMother(_mother);  addObject(_shooterAlien);
		_shooterAlien->setMother(_mother); _mother->addAlien(); addObject(_ufo);
	/*_sceneObjectList.push_back(_cannon);*/ };
	void mayGrantReward() {};
	virtual void render() const override ;
	virtual void update() override ;
	void handleEvent(const SDL_Event& event);
	void gameWin() { win = true; };
	void lose() { losed = true; };
	float getLandedHeight() const { return LandedHeight; };
	int getRandomRange(int min, int max);

	//Getters
	uint getCannonLifes() const { return _cannon->getnLifes(); };
	Vector2D<float> getLaser_Speed() const { return LASER_SPEED; };
	std::pair<uint, uint> getLaser_Size() const { return LASER_SIZE; };
};

