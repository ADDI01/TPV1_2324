#pragma once
#include <ostream>
#include "SceneObject.h"
using uint = unsigned int;
class Ufo : public SceneObject
{
private:
	enum ufoState {VISIBLE, OCULTO, DESTRUIDO};
	ufoState _actualState;
	float _occulTime;
	std::pair<int, int> minmaxOccultTime;
	SDL_Rect* _myRect = nullptr;

public:
	Ufo(Game* game,Vector2D<float> pos, Texture* texture, pair<uint,uint> size) :SceneObject(game,texture, pos, size,1)
		, _actualState(OCULTO), _occulTime(0/*sustituir por un random*/) {
		_myRect = new SDL_Rect; 
	};
	//constructora que recive el min & max de _occultTime

	void render() const override ;
	bool update() override { return false; };
	bool save() const override { return true; };
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override { return true; };
};

