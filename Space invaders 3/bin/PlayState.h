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
#include "checkML.h"

class SceneObject;
using uint = unsigned int;

class PlayState : public GameState
{
private:
	//SceneObject's pointers
	Mothership* _mother = nullptr;
	Cannon* _cannon = nullptr;
	Bunker* _bunker = nullptr;
	Alien* _alien = nullptr;
	ShooterAlien* _shooterAlien = nullptr;
	Ufo* _ufo = nullptr;
	Laser* _laser = nullptr;
	Star* star = nullptr;
	InfoBar* infoBar = nullptr;

	//SceneObjects constants
	const uint FONT_SIZE = 50;
	const uint CANNON_SPEED = 30;
	const uint ALIEN_SPEED = 4;
	const Vector2D<float> LASER_SPEED = Vector2D<float>(0, 5);
	std::pair<uint, uint> LASER_SIZE = std::pair<uint, uint>(5, 20);
	const Vector2D<float> REWARD_SPEED = Vector2D<float>(0, 10);
	std::pair<uint, uint> REWARD_SIZE = std::pair<uint, uint>(32, 33);
	const Point2D<float> INFOBAR_POS = Point2D<float>(10, WIN_HEIGHT - 30);
	std::pair<uint, uint> INFOBAR_SIZE = std::pair<uint, uint>(34, 21);
	const uint MOTHERSHIP_MOV_CD = 20;
	const uint MOTHERSHIP_LEVEL = 20;
	const int nLevels = 4;

	//Specific atributes
	int nLevel = 0;
	
	//condiciones del juego
	bool win = false;
	bool losed = false;
	float LandedHeight = 600;
	GameList<SceneObject,false> _sceneObjectList;
public:
	//has die, colisiones, etc.
	PlayState(SDLApplication* myGame) : GameState(myGame) { loadFromFile("./recursos/mapas/pred0.txt"); };
	~PlayState();
	void mayGrantReward() {};
	virtual void render() const override ;
	virtual void update() override ;
	void handleEvent(const SDL_Event& event);
	float getLandedHeight() const { return LandedHeight; };
	bool damage(SDL_Rect rect, Father father) const;
	void HasDied(GameList<SceneObject, false>::anchor itS);
	void addSceneObject(SceneObject* s) { _sceneObjectList.push_back(s); };
	void limpiaLista();
	void gameWin();

	void loadFromFile(std::string fileName);

	//Getters
	uint getCannonLifes() const { return _cannon->getnLifes(); };
	Vector2D<float> getLaser_Speed() const { return LASER_SPEED; };
	std::pair<uint, uint> getLaser_Size() const { return LASER_SIZE; };
	Vector2D<float> getReward_Speed() const { return REWARD_SPEED; };
	std::pair<uint, uint> getReward_Size() const { return REWARD_SIZE; };
	int getRandomRange(int min, int max);

	//setters
	void setWin() { win = true; };
	void setLose() { losed = true; };
};

