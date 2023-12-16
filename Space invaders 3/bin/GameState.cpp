#include "GameState.h"
#include "SceneObject.h"

GameState::~GameState(){
	eventHandlerList.clear();
}

void GameState::addEventListener(EventHandler* e){
	eventHandlerList.push_back(e);
}

void GameState::addObject(GameObject* g){
	gameList.push_back(g);
}