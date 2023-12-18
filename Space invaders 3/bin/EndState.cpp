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
