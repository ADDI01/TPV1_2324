#include "Save.h"
#include "SDLApplication.h"

Save::Save(SDLApplication* myapp, PlayState* second) : GameState(myapp), secondState(second)
{
}

void Save::render() const
{
	secondState->render();

	SDL_Rect rect = { 0,0,800,600 };
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(myGame->getRenderer(), 0, 0, 0, 200);
	SDL_RenderFillRect(myGame->getRenderer(), &rect);
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_NONE);

	rect.x = 200;
	rect.y = 200;
	rect.w = 400;
	rect.h = 100;
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(myGame->getRenderer(), 255, 255, 255, 200);
	SDL_RenderFillRect(myGame->getRenderer(), &rect);
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_NONE);
}

void Save::update()
{
}

void Save::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_0) { code += '0'; }
		else if (event.key.keysym.sym == SDLK_1) { code += '1'; }
		else if (event.key.keysym.sym == SDLK_2) { code += '2'; }
		else if (event.key.keysym.sym == SDLK_3) { code += '3'; }
		else if (event.key.keysym.sym == SDLK_4) { code += '4'; }
		else if (event.key.keysym.sym == SDLK_5) { code += '5'; }
		else if (event.key.keysym.sym == SDLK_6) { code += '6'; }
		else if (event.key.keysym.sym == SDLK_7) { code += '7'; }
		else if (event.key.keysym.sym == SDLK_8) { code += '8'; }
		else if (event.key.keysym.sym == SDLK_9) { code += '9'; }
		else if (code != "" && event.key.keysym.sym == SDLK_RETURN) {
			secondState->save("./recursos/mapas/" + code + ".txt");
			myGame->setguarda();
		}
	}
}
