#pragma once
#include "GameList.h"
#include <list>
#include "EventHandler.h"
#include "GameList.h"

class GameObject;
class Game;

class GameState
{
private:
	GameList<GameObject, true> gameList;
	std::list<EventHandler*> eventHandlerList;
	Game* _myGame;

public:
	void render() const;
	void update();
	void handleEvent();
	void addEventListener(EventHandler* e) {eventHandlerList.push_back(e);};
	void addObject(GameObject* g) {gameList.push_back(g);};
};