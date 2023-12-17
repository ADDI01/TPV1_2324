#include "PauseState.h"
#include "SDLApplication.h"

PauseState::PauseState(SDLApplication* myGame, Texture* continuarTexture, Texture* guardarPartidaTexture,
	Texture* cargarPartidaTexture, Texture* salirTexture) : GameState(myGame)
{
	Button* _button = new Button(continuarTexture, this, _cPos, _cSize);
	addObject(_button);
	addEventListener(_button);
	_button->connect([this]() { continuar(); });
	_button = new Button(guardarPartidaTexture, this, _gPPos, _gPSize);
	addObject(_button);
	addEventListener(_button);
	_button->connect([this]() { guardarPartida(); });
	_button = new Button(cargarPartidaTexture, this, _cPPos, _cPSize);
	addObject(_button);
	addEventListener(_button);
	_button->connect([this]() { cargarPartida(); });
	_button = new Button(salirTexture, this, _sPos, _sSize);
	addObject(_button);
	addEventListener(_button);
	_button->connect([this]() { salir(); });
	_button = nullptr;
}

PauseState::~PauseState()
{
	gameList.clear();
}

void PauseState::continuar()
{

}

void PauseState::guardarPartida()
{
}

void PauseState::cargarPartida()
{
}

void PauseState::salir()
{
	myGame->setExit();
}


void PauseState::render() const
{
	_myPlayState->render();

	for (auto it = gameList.begin(); it != gameList.end(); ++it)
	{
		(*it).render();
	}
}

void PauseState::update()
{
	for (auto it = gameList.begin(); it != gameList.end(); ++it) {
		(*it).update();
	}
}

void PauseState::handleEvent(const SDL_Event& event)
{
	for (EventHandler* it : eventHandlerList) {
		it->manageEvent(event);
	}
}