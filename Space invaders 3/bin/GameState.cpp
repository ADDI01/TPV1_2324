#include "GameState.h"
#include "SceneObject.h"
#include "EventHandler.h"
#include "SDLApplication.h"

GameState::~GameState(){
	gameList.clear();
	for (EventHandler* it : eventHandlerList) { delete it; it = nullptr; }
}

void GameState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* list : eventHandlerList) {
		list->manageEvent(event);
	}
}

void GameState::addEventListener(EventHandler* e){
	eventHandlerList.push_back(e);
}

void GameState::addObject(GameObject* g){
	gameList.push_back(g);
}