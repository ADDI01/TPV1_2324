#pragma once
#include "Vector2D.h"
#include "Texture.h"

	using namespace std;
	using uint = unsigned int;

	class Star
	{
	private:
		//posici�n del background
		Point2D<float> _pos;
		//puntero a su Textura
		Texture* _texture;
		//Tama�o del alien
		uint _w = 0, _h = 0;

	public:
		Star(Point2D<float> pos, Texture* texture, uint w, uint h) : _pos(pos), _texture(texture), _w(w), _h(h) {};

		void render() const {
			SDL_Rect destRect;
			destRect.x = 0;
			destRect.y = 0;
			destRect.w = _w;
			destRect.h = _h;

			_texture->render(destRect);
		};
	};