#include "Alien.h"

Alien::Alien(Point2D<float> pos, Texture* texture, uint w, uint h, Game* game, float velocity, int type, bool idle)
	:SceneObject(game,pos,std::pair<int,int> (w,h),1), _texture(texture), _velocity(velocity), _subType(type), _idle(idle) {_myRect = new SDL_Rect;};

void Alien::render() const
{
	_myRect->x = pos.getX();
	_myRect->y = pos.getY();
	_myRect->w = dimensiones.first;
	_myRect->h = dimensiones.second;

	//The alien is rendered depending on the subtype. 0 for shooters, 1 for greens, 2 for reds
	//Idle defines which frame is rendered. False for 1st frame, True for 2nd
	switch (_subType) {
	case 0:
		if (!_idle) _texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(*_myRect, 0, 1, SDL_FLIP_NONE);
		break;
	case 1:
		if (!_idle) _texture->renderFrame(*_myRect, 1, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(*_myRect, 1, 1, SDL_FLIP_NONE);
		break;
	case 2:
		if (!_idle) _texture->renderFrame(*_myRect, 2, 0, SDL_FLIP_NONE);
		else _texture->renderFrame(*_myRect, 2, 1, SDL_FLIP_NONE);
		break;
	default:
		//When non expected alien comes
		throw "The Alien does not exist.";
		break;
	}
}

bool Alien:: update()
{
bool ret = true;
if (_subType == -1) //The alien's dead
{
	ret = false;
}
else
{
	/*pos = pos + (myGame->getDirection() * _velocity); //Alien moves

	if (pos.getX() >= myGame->getWidth() - dimensiones.first || pos.getX() <= 0) //Alien tries to move out of lateral limits
	{
		myGame->cannotMove();
	}

	if (_subType == 0 && _shootCD <= 0) //Shooter alien shoot
	{
		_shootCD = _myGame->getRandomRange(MIN_CD, MAX_CD);
		_myGame->fireLaser(this); //Instanciate alien's laser
	}
	else
	{
		_shootCD--;
	}
	_idle = !_idle;
}
if (pos.getY() >= myGame->getHeight() - dimensiones.second) //If aliens reach the bottom, the game ends
{
	myGame->lose();
}*/
	pos = pos + Vector2D<float>(1, 0) * _velocity;
	_idle = !_idle;
}
return ret;
}


bool Alien::hit(SDL_Rect AttackRect, int typeOfDamage) {
	if (SDL_HasIntersection(&AttackRect, _myRect)) 
	{
		_subType = -1;
		return true;
	}
	else 
	{
		return false;
	}
}

void Alien::bajaColumna() {
	pos = pos + Vector2D<float>(0, dimensiones.second);
}