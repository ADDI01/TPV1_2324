#include "Button.h"

void Button::connect(CallBack cB){
	_myCallbacks.push_back(cB);
}

void Button::render() const
{
	if (_encima) {
		SDL_Color color;
		color.r = 124;
		color.g = 252;
		color.b = 0;
		_texture->render(_myRect, color);
	}
	else 
		_texture->render(_myRect);
}

void Button::update(){
	int x, y;
	SDL_GetMouseState(&x, &y);

	// Comprueba si el rat�n est� sobre el rect�ngulo
	_encima = x >= _myRect.x && x <= _myRect.x + _myRect.w && y >= _myRect.y && y <= _myRect.y + _myRect.h;
	if (_encima)
		std::cout << "a";
	std::cout <<x << std::endl;
}