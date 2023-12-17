#pragma once
#include "GameState.h"
#include "Cannon.h"

class SceneObject;

class PlayState : public GameState
{
private:
	//SceneObject's pointers
	//Mothership* _mother = nullptr;
	//Cannon* _cannon = nullptr;
	//Bunker* _bunker = nullptr;
	//Alien* _alien = nullptr;
	//ShooterAlien* _shooterAlien = nullptr;
	//Ufo* _ufo = nullptr;
	//Laser* _laser = nullptr;
	//Star* star = nullptr;
	//InfoBar* infoBar = nullptr;

	//SceneObjects constants
	// uint CANNON_SPEED = 30;
	//const uint ALIEN_SPEED = 4;
	//const Vector2D<float> LASER_SPEED = Vector2D<float>(0, 5);
	//std::pair<uint, uint> LASER_SIZE = std::pair<uint, uint>(5, 20);
	//const Point2D<float> INFOBAR_POS = Point2D<float>(10, WIN_HEIGHT - 30);
	//std::pair<uint, uint> INFOBAR_SIZE = std::pair<uint, uint>(34, 21);
	//const uint MOTHERSHIP_MOV_CD = 20;

	GameList<SceneObject*, false> _sceneObjectList;

public:
	//has die, colisiones, etc.
	void mayGrantReward() {};
	virtual void render() const override ;
	virtual void update() override {};
};

