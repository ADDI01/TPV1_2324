#include "EndState.h"
#include "SDLApplication.h"

void EndState::volver()
{
	myGame->setvuelveMenu();
}

void EndState::salir()
{
	myGame->setExit();
}

EndState::EndState(SDLApplication* myGame, Texture* vMT, Texture* sT) : GameState(myGame)
{
	Button* _button = new Button(vMT, this, _vMPos, _vMSize);
	addObject(_button);
	addEventListener(_button);
	_button->connect([this]() {volver(); });
	_button = new Button(sT, this, _sPos, _sSize);
	addObject(_button);
	addEventListener(_button);
	_button->connect([this]() { salir(); });
}

void EndState::render() const
{
	SDL_Rect _myRect;
	_myRect.x = 0;
	_myRect.y = 0;
	_myRect.w = myGame->getWidth();
	_myRect.h = myGame->getHeight();

	SDL_SetRenderDrawColor(myGame->getRenderer(), 0, 0, 0, 0x0);
	SDL_RenderFillRect(myGame->getRenderer(), &_myRect);
	for (auto it = gameList.begin(); it != gameList.end(); ++it)
	{
		(*it).render();
	}
}

void EndState::update()
{
	for (auto it = gameList.begin(); it != gameList.end(); ++it) {
		(*it).update();
	}
}

void EndState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* it : eventHandlerList) {
		it->manageEvent(event);
	}
}
