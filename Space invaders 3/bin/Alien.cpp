#include "Alien.h"
#include "PlayState.h"
#include "SDLError.h"

using namespace std;

Alien::Alien(Point2D<float> pos, Texture* texture, pair<uint, uint> size, GameState* game, PlayState* myPlayState, SDLApplication* app,
	float velocity, int type, bool idle): SceneObject(game, myPlayState, app,texture, pos, size, 1), _velocity(velocity),
	_subType(type), _idle(idle), _myRect(SDL_Rect()) {
}; 

Alien::Alien(GameState* game, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture, uint velocity, int lastestRow) :
	SceneObject(game, myPlayState, app, in, texture, 1), _velocity(velocity)
{
	in >> _subType;
	if (lastestRow == -1 || lastestRow != -1 && lastestRow != _pos.getY()) {
		lastestRow = _pos.getY();
		_idle = false;
	}
	else _idle = !_idle;
};
 
Alien:: ~Alien() {
	_texture = nullptr;
	_myGame = nullptr;
	_mother = nullptr;
};

void Alien::render() const {
	//The alien is rendered depending on the subtype. 0 for shooters, 1 for greens, 2 for reds
	//Idle defines which frame is rendered. False for 1st frame, True for 2nd
	switch (_subType) {
	case 0:
		if (!_idle) _texture->renderFrame(_myRect, 0, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(_myRect, 0, 1, SDL_FLIP_NONE);
		break;
	case 1:
		if (!_idle) _texture->renderFrame(_myRect, 1, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(_myRect, 1, 1, SDL_FLIP_NONE);
		break;
	case 2:
		if (!_idle) _texture->renderFrame(_myRect, 2, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(_myRect, 2, 1, SDL_FLIP_NONE);
		break;
	default:
		//When non expected alien comes
		throw SDLError("The Alien does not exist.");
		break;
	}
}

void Alien:: update()
{
	if (_mother->shouldMove()) {
		_pos = _pos + _mother->getDirection();
		_idle = !_idle;
		if ((_pos.getX() >= _myApp->getWidth() - _size.first && _mother->getDirection().getX() >= 0) 
			|| (_pos.getX() <= 0 && _mother->getDirection().getX() <= 0))
		{
			_mother->lowerColumn();
		}
	}

	if (_mother->alienLanded(_pos.getY())) {
		_mother->haveLanded();
	}

	//Alien's Dest_Rect is modified
	_myRect.x = _pos.getX();
	_myRect.y = _pos.getY();
	_myRect.w = _size.first;
	_myRect.h = _size.second;
}

void Alien::save(std::ostream& out) const {
	out << 1 << " " << _pos.getX() << " " << _pos.getY() << " " << _subType << endl;
}

bool Alien::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (typeOfDamage != ALIEN && typeOfDamage != UFO &&  SDL_HasIntersection(&AttackRect, &_myRect)) //Cannon bullet collides an alien
	{
		if (_subType != -1) { //Alien is declared dead
			_myPlayState->getInfoBar()->setPoints(_subType);
			_subType = -1;
			_myPlayState->HasDied(_itS);
			_mother->alienDied();
		}
		return true;
	}
	else 
	{
		return false;
	}
}

void Alien::lowerColumn() {
	_pos = _pos + Vector2D<float>(0, _size.second);
}