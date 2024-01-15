#pragma once
#include "PlayState.h"
#include "checkML.h"
#include <SDL_ttf.h>

using uint = unsigned int;

class Save : public GameState {
private:
	//Match code
	std::string code;
	//Color of the code written
	SDL_Color color;
	//Something is written
	bool written = false;
	//Rect of the code
	SDL_Rect _codeRect;
	//Offset from box to where code is written
	uint _offset;
	//Pointer to font
	TTF_Font* font = nullptr;
	//Pointer to texture
	SDL_Texture* _codeTexture = nullptr;
	//Pointer to surface
	SDL_Surface* surf = nullptr;
	//Pointer to renderer
	SDL_Renderer* _renderer = nullptr;
	//Second state
	PlayState* secondState;
public:
	Save(SDLApplication* myapp, PlayState* second, SDL_Renderer* renderer);
	virtual void render() const override;
	virtual void update() override;
	void handleEvent(const SDL_Event& event);
};