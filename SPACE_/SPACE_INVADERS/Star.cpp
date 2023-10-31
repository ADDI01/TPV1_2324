#include "Star.h"

void Star::render() const {
	SDL_Rect destRect;
	destRect.x = 0;
	destRect.y = 0;
	destRect.w = _w;
	destRect.h = _h;

	_texture->render(destRect);
}
