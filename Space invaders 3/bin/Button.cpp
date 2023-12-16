#include "Button.h"

void Button::connect(CallBack cB){
	_myCallbacks.push_back(cB);
}

void Button::render() const
{
	SDL_Color color;
	color.r = 124;
	color.g = 252;
	color.b = 0;
	_texture->render(_myRect, color);
	//_texture->render(_myRect);
}

void Button::update(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (_myRect.x <= x + _myRect.w && _myRect.x >= x && _myRect.y >= y + _myRect.y && _myRect.y <= y) {
		std::cout << "a";
	}
	std::cout << x << std::endl;
}
