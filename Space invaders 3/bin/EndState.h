#pragma once
#include "GameState.h"
#include "Vector2D.h"
#include "texture.h"
#include "Button.h"
#include "checkML.h"
class EndState: public GameState
{
private:
	//volver al menú
	std::pair<unsigned int, unsigned int>_vMSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _vMPos = Point2D<float>(400 - _vMSize.second / 2, 50);
	//salir
	std::pair<unsigned int, unsigned int>_sSize = std::pair<unsigned int, unsigned int>(20, 100);
	Point2D<float> _sPos = Point2D<float>(400 - _sSize.second / 2, 350);

	//callBacks
	void volver();
	void salir();

public:
	EndState(SDLApplication* myGame,Texture* vMT, Texture* sT);

	void render() const override;
	void update() override;
	void handleEvent(const SDL_Event& event) override;
};