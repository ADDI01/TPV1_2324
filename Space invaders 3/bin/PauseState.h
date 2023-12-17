#pragma once
#include "GameState.h"
#include "texture.h" 
#include "Button.h"
#include "PlayState.h"

class PauseState : public GameState
{
private:
	//continuar
	std::pair<unsigned int, unsigned int>_cSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _cPos = Point2D<float>(400 - _cSize.second / 2, 100);
	//guardar partida
	std::pair<unsigned int, unsigned int>_gPSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _gPPos = Point2D<float>(400 - _gPSize.second / 2, 400);
	//carga de partida
	std::pair<unsigned int, unsigned int>_cPSize = std::pair<unsigned int, unsigned int>(20, 200);
	Point2D<float> _cPPos = Point2D<float>(400 - _cPSize.second / 2, 250);
	// salir
	std::pair<unsigned int, unsigned int>_sSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _sPos = Point2D<float>(400 - _sSize.second / 2, 550);

	PlayState* _myPlayState;

	//callbacks de los botones
	void continuar();
	void guardarPartida();
	void cargarPartida();
	void salir();

public:
	PauseState(SDLApplication* myGame, Texture* continuar, Texture* guardarPartida, Texture* cargarPartida, Texture* salir);
	~PauseState();
	void setPlayState(PlayState* p) { _myPlayState = p; };
	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;
};

