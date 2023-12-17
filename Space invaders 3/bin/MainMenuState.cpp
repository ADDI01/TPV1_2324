#include "MainMenuState.h"
#include "SDLApplication.h"

MainMenuState::MainMenuState(SDLApplication* myGame,Texture* myTexture, Texture* nuevaPartida, Texture* cargarPartida, Texture* salir) : GameState(myGame), _texture(myTexture){
	Button* _button = new Button(nuevaPartida, this, _nPPos, _nPSize);
	gameList.push_back(_button);
	eventHandlerList.push_back(_button);
	_button = new Button(cargarPartida, this, _cPPos,_cPSize);
	gameList.push_back(_button);
	eventHandlerList.push_back(_button);
	_button = new Button(salir, this, _sPos,_sSize);
	gameList.push_back(_button);
	eventHandlerList.push_back(_button);

	_button->connect([this]() { exit(); });
	_button = nullptr;
}

void MainMenuState::exit()
{
	myGame->exitGame();
}

void MainMenuState::render() const{
	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = 800;
	destRect.h = 600;
	_texture->render(destRect);

	for (auto it = gameList.begin(); it != gameList.end(); ++it) 
	{
		(*it).render();
	}
}

void MainMenuState::update(){
	for (auto it = gameList.begin(); it != gameList.end(); ++it) {
		(*it).update();
	}
}

void MainMenuState::handleEvent(const SDL_Event &event){
	for (EventHandler* it : eventHandlerList) {
		it->manageEvent(event);
	}
}