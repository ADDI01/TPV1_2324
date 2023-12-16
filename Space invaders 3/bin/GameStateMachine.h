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
	//algoritmos propios de la máquina
	void pushState(GameState* g);
	void replaceState(GameState* g);
	void popState();
	bool empty() { return statesMachine.empty(); };

	// procedimientos de los estados
	void update();
	void render();
	void handleEvent();
};