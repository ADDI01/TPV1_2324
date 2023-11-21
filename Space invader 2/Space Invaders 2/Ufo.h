#pragma once
#include <ostream>
#include "SceneObject.h"
class Ufo : public SceneObject
{
private:
	enum ufoState {VISIBLE, OCULTO, DESTRUIDO};
	ufoState _actualState;
	float _occulTime = 0.0f; // Sustituir por el rangom de game
	std::pair<int, int> minmaxOccultTime;

public:
	Ufo() : _actualState(OCULTO), _occulTime(0/*sustituir por un random*/) {};
	//constructora que recive el min & max de _occultTime

};

