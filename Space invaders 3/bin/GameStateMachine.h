#pragma once
#include <stack>
#include "GameState.h"
class GameStateMachine
{
public:
	std::stack<GameState*> statesMachine;
	void pushState() {};
	void replaceState() {};
	void popState() {};
	void update() {};
	void render() {};
	void handleEvent() {};
};