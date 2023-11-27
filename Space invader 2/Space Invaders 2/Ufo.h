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

public:
	Ufo(Game* game,Vector2D<float> pos, Texture texture, uint w,uint h) :SceneObject(game,nullptr, pos,std::pair(w,h),1), _actualState(OCULTO), _occulTime(0/*sustituir por un random*/) {};
	//constructora que recive el min & max de _occultTime

};

