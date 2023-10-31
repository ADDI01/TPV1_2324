#include "Star.h"

void Star::render() const {
	SDL_Rect destRect;
	destRect.x = _pos.getX();
	destRect.y = _pos.getY();
	destRect.w = _w;
	destRect.h = _h;

	_texture->render(destRect);
}
