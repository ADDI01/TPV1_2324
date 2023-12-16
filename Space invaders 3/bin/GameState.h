#pragma once
#include "GameList.h"
#include <list>
#include "EventHandler.h"
#include "GameList.h"
#include"checkML.h"
#include "GameObject.h"

class Game;

class GameState
{
protected:
	GameList<GameObject, true> gameList;
	std::list<EventHandler*> eventHandlerList;
	Game* myGame;

public:
	virtual ~GameState() = 0;
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent() = 0;
	void addEventListener(EventHandler* e);
	void addObject(GameObject* g);
};