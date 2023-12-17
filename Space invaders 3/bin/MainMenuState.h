#pragma once
#include "GameState.h"
#include "texture.h" 
#include "Button.h"
#include <vector>
class MainMenuState : public GameState
{
private:
	Texture* _texture;
	//nueva partida

	std::pair<unsigned int, unsigned int>_nPSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _nPPos = Point2D<float>(400 - _nPSize.second/2,150) ;
	//carga de partida

	std::pair<unsigned int, unsigned int>_cPSize = std::pair<unsigned int, unsigned int>(20, 200);
	Point2D<float> _cPPos = Point2D<float>(400 - _cPSize.second/2, 200);
	// salir

	std::pair<unsigned int, unsigned int>_sSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _sPos = Point2D<float>(400 - _sSize.second/2, 250);

public:
	MainMenuState(Texture* myTexture, Texture* nuevaPartida, Texture* cargarPartida, Texture* salir);

	void render() const override;
	void update() override;
	void handleEvent() override;
};
