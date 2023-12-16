#pragma once
#include "GameList.h"
#include <list>
#include "EventHandler.h"
#include "GameList.h"
#include"checkML.h"

class GameObject;
class Game;

class GameState
{
private:
	GameList<GameObject, true> gameList;
	std::list<EventHandler*> eventHandlerList;
	Game* myGame;

public:
	GameState();
	~GameState();
	void render() const;
	void update();
	void handleEvent();
	void addEventListener(EventHandler* e);
	void addObject(GameObject* g);
};