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

	// Comprueba si el ratón está sobre el rectángulo
	_encima = x >= _myRect.x && x <= _myRect.x + _myRect.w && y >= _myRect.y && y <= _myRect.y + _myRect.h;
}

void Button::manageEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && _encima) {
		for (CallBack c : _myCallbacks) {
			c();
		}
	}
}
