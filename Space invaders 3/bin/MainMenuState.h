#pragma once
#include "GameState.h"
#include "texture.h" 
#include "Button.h"
class MainMenuState : public GameState
{
private:
	Texture* _texture;
	Button _nuevaPartida, _cargarPartida, _salir;
	//nueva partida
	Point2D<float> _nPPos = Point2D<float>(100,100);
	//carga de partida
	Point2D<float> _cPPos = Point2D<float>(200, 100);
	// salir
	Point2D<float> _sPos = Point2D<float>(300, 100);

public:
	MainMenuState(Texture* myTexture, Texture* nuevaPartida, Texture* cargarPartida, Texture* salir) : _texture(myTexture), _nuevaPartida(nuevaPartida, this, _nPPos),
		_cargarPartida(cargarPartida, this, _cPPos), _salir(salir, this, _sPos) {
		gameList.push_back(&_nuevaPartida); gameList.push_back(&_cargarPartida); gameList.push_back(&_salir);
	};

	void render() const override;
	void update() override;
	void handleEvent() override;
};

