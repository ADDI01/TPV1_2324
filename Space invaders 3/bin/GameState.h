#pragma once
#include "GameList.h"
#include <list>
#include "EventHandler.h"
#include "GameList.h"
#include"checkML.h"
#include "GameObject.h"

class SDLApplication;

class GameState
{
protected:
	GameList<GameObject, true> gameList;
	std::list<EventHandler*> eventHandlerList;
	SDLApplication* myGame;

public:
	GameState(SDLApplication* myGame) : myGame(myGame) {};
	//virtual void HasDied(GameList < GameObject, true>::anchor it);
	virtual ~GameState();
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent(const SDL_Event& event);
	void addEventListener(EventHandler* e);
	void addObject(GameObject* g);
};