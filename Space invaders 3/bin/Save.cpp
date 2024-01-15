#include "Save.h"
#include "SDLApplication.h"

Save::Save(SDLApplication* myapp, PlayState* second, SDL_Renderer* renderer) : GameState(myapp), secondState(second),
		_renderer(renderer)
{
	std::string filename = "./SDL2_ttf-2.20.2/PressStart2P-Regular.ttf";
	_offset = 20;

	color.r = 0;
	color.g = 0;
	color.b = 0;

	_codeRect.x = 200 + _offset;
	_codeRect.y = 200 + _offset;
	_codeRect.w = 30;
	_codeRect.h = 60;

	font = TTF_OpenFont(filename.c_str(), 30);
	surf = TTF_RenderUTF8_Solid(font, code.c_str(), color);
	_codeTexture = SDL_CreateTextureFromSurface(_renderer, surf);
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
	SDL_RenderCopy(_renderer, _codeTexture, nullptr, &_codeRect);
}

void Save::update()
{
	if (written == true) {
		_codeRect.w = 30 * code.size();
		surf = TTF_RenderUTF8_Solid(font, code.c_str(), color);
		_codeTexture = SDL_CreateTextureFromSurface(_renderer, surf);
		written = false;
	}
}

void Save::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN) { written = true;
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
		else if (code != "" && event.key.keysym.sym == SDLK_RETURN) { //Error aqui
			secondState->save("./recursos/mapas/" + code + ".txt");
			myGame->setguarda();
		}
	}
}
