#include "GameStateMachine.h"
#include <SDL.h>

GameStateMachine::~GameStateMachine(){
	while (!statesMachine.empty()) {
		popState();
	}
}

void GameStateMachine::  pushState(GameState* g) {
	statesMachine.push(g);
}

void GameStateMachine::replaceState(GameState* g){
	popState();
	pushState(g);
}

void GameStateMachine::popState(){
	delete statesMachine.top();
	statesMachine.pop();
}

void GameStateMachine::update(){
	statesMachine.top()->update();
}

void GameStateMachine::render(){
	statesMachine.top()->render();
}

void GameStateMachine::handleEvent(const SDL_Event& event){
	statesMachine.top()->handleEvent(event);
}