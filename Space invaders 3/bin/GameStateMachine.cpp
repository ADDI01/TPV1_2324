#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine(){
	while (!statesMachine.empty()) {
		delete statesMachine.top();
		statesMachine.pop();
	}
}

void GameStateMachine::  pushState(GameState* g) {
	statesMachine.push(g);
}

void GameStateMachine::replaceState(GameState* g){
	statesMachine.pop();
	pushState(g);
}

void GameStateMachine::popState(){
	statesMachine.pop();
}

void GameStateMachine::update(){
	statesMachine.top()->update();
}

void GameStateMachine::render(){
	statesMachine.top()->render();
}

void GameStateMachine::handleEvent(){
	statesMachine.top()->handleEvent();
}