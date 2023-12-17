#include "Button.h"

void Button::connect(CallBack cB){
	_myCallbacks.push_back(cB);
}

void Button::render() const
{
	if (_encima) {
		SDL_Color color; // n�meros m�gicos (verde)
		color.r = 124;
		color.g = 252;
		color.b = 0;
		_texture->render(_myRect, color);
	}
	else 
		_texture->render(_myRect);
}

void Button::update(){
	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);

	// Comprueba si el rat�n est� sobre el rect�ngulo
	_encima = SDL_PointInRect(&point, &_myRect);
	/*int x, y;
	SDL_GetMouseState(&x, &y);
	*/
	// Comprueba si el rat�n est� sobre el rect�ngulo
	//_encima = x >= _myRect.x && x <= _myRect.x + _myRect.w && y >= _myRect.y && y <= _myRect.y + _myRect.h;
}

void Button::manageEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN && _encima) {
		for (CallBack c : _myCallbacks) {
			c();
		}
	}
}
