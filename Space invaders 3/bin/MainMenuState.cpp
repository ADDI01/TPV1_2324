#include "MainMenuState.h"

MainMenuState::MainMenuState(Texture* myTexture, Texture* nuevaPartida, Texture* cargarPartida, Texture* salir) : _texture(myTexture){
	gameList.push_back(&Button(nuevaPartida, this, _nPPos, _nPSize));
	gameList.push_back(&Button(cargarPartida, this, _cPPos,_cPSize));
	gameList.push_back(&Button(salir, this, _sPos,_sSize));
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

void MainMenuState::handleEvent(){

}
