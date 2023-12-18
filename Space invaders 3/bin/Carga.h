#pragma once
#include "GameState.h"
#include <string>


class Carga : public GameState {
private:
	std::string code;
	GameState* secondState;
public:
	Carga(SDLApplication* myapp, GameState* second);
	virtual void render() const override;
	virtual void update() override;
	void handleEvent(const SDL_Event& event);
};