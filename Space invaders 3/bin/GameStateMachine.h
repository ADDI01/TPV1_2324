#pragma once
#include <stack>
#include "GameState.h"
#include"checkML.h"
class GameStateMachine
{
private:
	std::stack<GameState*> statesMachine;
public:
	~GameStateMachine();
	void pushState(GameState* g);
	void replaceState(GameState* g);
	void popState();
	void update();
	void render();
	void handleEvent();
};