#include "Ufo.h"
#include "Game.h"
#include <fstream>


void Ufo::render() const
{
	_myRect->x = _pos.getX() - (_size.first / 2);
	_myRect->y = _pos.getY();
	_myRect->w = _size.first;
	_myRect->h = _size.second;

	switch (_actualState)
	{
	case Ufo::VISIBLE:
		_texture->renderFrame(*_myRect, 0, 0, SDL_FLIP_NONE);
		break;
	case Ufo::OCULTO:
		break;
	case Ufo::DESTRUIDO:
		_texture->renderFrame(*_myRect, 0, 1, SDL_FLIP_NONE);
		break;
	default:
		throw "no ufo";
		break;
	}
}

void Ufo::update() 
{
	updateState();
}

void Ufo::updateState() {
	switch (_actualState)
	{
	case Ufo::VISIBLE:
		_pos = _pos + Vector2D<float>(-4.5, 0);
		if (_pos.getX() <= -57) {
			_actualState = OCULTO;
			_actualOccultTime = _game->getRandomRange(200, 300);
		}
		break;
	case Ufo::OCULTO:
		if (_actualOccultTime > 0)
			_actualOccultTime--;
		else {
			_actualOccultTime = _occultTime;
			_pos = _initialPos;
			_actualState = VISIBLE;
		}
		break;
	case Ufo::DESTRUIDO:
		if (_actualDieTime == _dieTime) {
			_actualState = OCULTO;
			_pos = Vector2D<float>(0, 0);
			_actualDieTime = 0;
		}
		else
			_actualDieTime++;
		break;
	default:
		break;
	}
}

bool Ufo::hit(SDL_Rect AttackRect, int typeOfDamage)
{
	if (_actualState == VISIBLE &&typeOfDamage != 0 && SDL_HasIntersection(&AttackRect, _myRect))
	{
		_actualState = DESTRUIDO;
		return true;
	}
	else
	{
		return false;
	}
}

void Ufo::save(std::ostream& out) const {
	out << 5 << " " << _pos.getX() << " " << _pos.getY() << " " << _actualState << " " << _occultTime << endl;
}