#pragma once
#include <ostream>
#include "SceneObject.h"

using uint = unsigned int;

class Ufo : public SceneObject
{
private:
	enum ufoState {OCULTO, VISIBLE, DESTRUIDO};
	ufoState _actualState;
	float _occultTime;
	float _actualOccultTime;
	std::pair<int, int> minmaxOccultTime;
	SDL_Rect* _myRect = nullptr;
	float _dieTime = 3;
	float _actualDieTime = 0;
	Vector2D<float> _initialPos;

public:
	//constructora que recive el min & max de _occultTime
	Ufo(Game* game,Vector2D<float> pos, Texture* texture, pair<uint,uint> size, float state, float wait): SceneObject(game,texture, 
		pos, size,1), _initialPos(pos), _actualState((ufoState) state), _occultTime(wait) {
		_myRect = new SDL_Rect; 
		_actualOccultTime = _occultTime;
	};
	~Ufo() {
		_texture = nullptr;
		_game = nullptr;
		delete _myRect;
		_myRect = nullptr;
	};

	void render() const override ;
	bool update() override;
	bool save() const override { return true; };
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	void updateState();
};

