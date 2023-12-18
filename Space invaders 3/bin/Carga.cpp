#include "Carga.h"
#include "PlayState.h"
#include "SDLApplication.h"

Carga::Carga(SDLApplication* myapp, GameState* second) : GameState(myapp), secondState(second)
{
}

void Carga::render() const
{
	secondState->render();

	SDL_Rect rect = { 0,0,800,600 };
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(myGame->getRenderer(), 0, 0, 0, 200);
	SDL_RenderFillRect(myGame->getRenderer(), &rect);
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_NONE);

	rect.x = 300;
	rect.y = 440;
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(myGame->getRenderer(), 255, 255, 255, 200);
	SDL_RenderFillRect(myGame->getRenderer(), &rect);
	SDL_SetRenderDrawBlendMode(myGame->getRenderer(), SDL_BLENDMODE_NONE);



}

void Carga::update()
{
}

void Carga::handleEvent(const SDL_Event& event)
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
	else if(code != "" && event.key.keysym.sym == SDLK_RETURN) {
		myGame->setCarga("./recursos/mapas/" + code + ".txt");
		}
	}
}
