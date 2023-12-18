#include "InfoBar.h"
#include "SDLError.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include <string>

using namespace std;

InfoBar::InfoBar(GameState* game, SDL_Renderer* renderer, PlayState* myPlayState, Texture* texture, Point2D<float> pos,
	pair<uint, uint> size, uint points, uint fontSize)
	: GameObject(game), _renderer(renderer), _texture(texture), _points(points), _pos(pos), _size(size), 
	_myPlayState(myPlayState), _fontSize(fontSize)
{
	string filename = "./SDL2_TTF/PressStart2P-Regular(1).ttf";

	color.r = 0;
	color.g = 0;
	color.b = 0;

	font = TTF_OpenFont(filename.c_str(), fontSize);
	surf = TTF_RenderUTF8_Solid(font, to_string(_points).c_str(), color);
	_pointsTexture = SDL_CreateTextureFromSurface(renderer, surf);

	
}; //TODO: Pasar Rects de las vidas en el constructor por param


InfoBar::~InfoBar() {
	_texture = nullptr;
	//TTF_CloseFont(font);
};

void InfoBar::render() const {
	switch (_myPlayState->getCannonLifes()) { //Renders the current number of cannon's lifes
	case 0:
		break;
	case 1:
		_texture->render(_cannonLife1);
		break;
	case 2:
		_texture->render(_cannonLife1);
		_texture->render(_cannonLife2);
		break;
	case 3:
		_texture->render(_cannonLife1);
		_texture->render(_cannonLife2);
		_texture->render(_cannonLife3);
		break;
	default:
		throw SDLError("Numero de cannons incorrecto.");
	}

	//Renders the points
	SDL_RenderCopy(_renderer, _pointsTexture, nullptr, &_pointsRect);
}

void InfoBar::update() {
	surf = TTF_RenderUTF8_Solid(font, to_string(_points).c_str(), color);
	_pointsTexture = SDL_CreateTextureFromSurface(_renderer, surf);

	_cannonLife1.w = _cannonLife2.w = _cannonLife3.w = _texture->getFrameWidth();
	_cannonLife1.h = _cannonLife2.h = _cannonLife3.h = _texture->getFrameHeight();
	_cannonLife1.y = _cannonLife2.y = _cannonLife3.y = WIN_HEIGHT - _texture->getFrameHeight() - _offset;
	_cannonLife1.x = _offset;
	_cannonLife2.x = _texture->getFrameWidth() + _offset * 2;
	_cannonLife3.x = _texture->getFrameWidth() * 2 + _offset * 3;

	_pointsRect.x = WIN_WIDTH - to_string(_points).size() * _fontSize - _offset;
	_pointsRect.y = WIN_HEIGHT - _offset;
	_pointsRect.w = to_string(_points).size() * _fontSize;
	_pointsRect.h = 50;
}

void InfoBar::setPoints(uint type) {
	switch (type)
	{
	case 0: //Shooter
		_points += 30;
		break;
	case 1: //Small
		_points += 20;
		break;
	case 2: //Big
		_points += 10;
	case 3: //UFO
		_points += 100;
		break;
	default:
		SDLError r("Enemigo incorrecto.");
		throw r.what();
		break;
	}
}
