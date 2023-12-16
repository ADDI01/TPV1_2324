#include "Button.h"

void Button::connect(CallBack cB){
	_myCallbacks.push_back(cB);
}

void Button::render() const
{
	SDL_Rect _myRect;
	_myRect.x = _pos.getX();
	_myRect.y = _pos.getY();
	_myRect.h = _rectSize.first;
	_myRect.w = _rectSize.second;
	_texture->render(_myRect);
}
