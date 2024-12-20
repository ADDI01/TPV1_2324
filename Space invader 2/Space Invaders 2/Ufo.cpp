#include "Ufo.h"
#include "Game.h"

Ufo::Ufo(Game* game, Vector2D<float> pos, Texture* texture, std::pair<uint, uint> size, int state, float wait): 
	SceneObject(game, texture, pos, size, 1), _initialPos(800, pos.getY()), _currentState((ufoState)state), 
	_occultTime(wait), _myRect(SDL_Rect()) 
{
	_currentOccultTime = _occultTime;
};

Ufo::Ufo(Game* game, std::ifstream& in, Texture* texture) : SceneObject(game, in, texture, 1), 
	_initialPos(WIN_WIDTH, _pos.getY()), _myRect(SDL_Rect())
{
	int state; //Aux to get the Ufo state

	in >> state;
	_currentState = (ufoState)state;
	in >> _occultTime;
	_currentOccultTime = _occultTime;
};

Ufo::~Ufo() {
	_texture = nullptr;
	_game = nullptr;
};

void Ufo::render() const
{
	switch (_currentState)
	{
	case Ufo::VISIBLE:
		_texture->renderFrame(_myRect, 0, 0, SDL_FLIP_NONE);
		break;
	case Ufo::OCULTO:
		break;
	case Ufo::DESTRUIDO:
		_texture->renderFrame(_myRect, 0, 1, SDL_FLIP_NONE);
		break;
	default:
		throw SDLError("No UFO");
		break;
	}
}

void Ufo::update() 
{
	updateState();

	//UFO's Dest_Rect is modified
	_myRect.x = _pos.getX() - (_size.first / 2);
	_myRect.y = _pos.getY();
	_myRect.w = _size.first;
	_myRect.h = _size.second;
}

void Ufo::updateState() {
	switch (_currentState)
	{
	case Ufo::VISIBLE:
		_pos = _pos + Vector2D<float>(-4, 0);
		if (_pos.getX() <= -57) {
			_currentState = OCULTO;
			_currentOccultTime = _game->getRandomRange(200, 300);
		}
		break;
	case Ufo::OCULTO:
		if (_currentOccultTime > 0)
			_currentOccultTime--;
		else {
			_currentOccultTime = _occultTime;
			_pos = _initialPos;
			_currentState = VISIBLE;
		}
		break;
	case Ufo::DESTRUIDO:
		if (_currentDieTime == _dieTime) {
			_currentState = OCULTO;
			_pos = Vector2D<float>(0, 0);
			_currentDieTime = 0;
		}
		else
			_currentDieTime++;
		break;
	default:
		break;
	}
}

void Ufo::save(std::ostream& out) const {
	out << 5 << " " << _pos.getX() << " " << _pos.getY() << " " << _currentState << " " << _occultTime << std::endl;
}

bool Ufo::hit(SDL_Rect AttackRect, int typeOfDamage)
{
	if (_currentState == VISIBLE &&typeOfDamage != 0 && SDL_HasIntersection(&AttackRect, &_myRect))
	{
		_currentState = DESTRUIDO;
		return true;
	}
	else
	{
		return false;
	}
}