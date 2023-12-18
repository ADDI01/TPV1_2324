#pragma once
#include "PlayState.h"
#include "checkML.h"

class Save : public GameState {
private:
	std::string code;
	PlayState* secondState;
public:
	Save(SDLApplication* myapp, PlayState* second);
	virtual void render() const override;
	virtual void update() override;
	void handleEvent(const SDL_Event& event);
};