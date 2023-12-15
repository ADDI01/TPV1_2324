#pragma once
#include "GameState.h"

class SceneObject;

class PlayState : public GameState
{
private:
	GameList<SceneObject> sceneObjectList;

public:
	//has die, colisiones, etc.
	void mayGrantReward();
};

