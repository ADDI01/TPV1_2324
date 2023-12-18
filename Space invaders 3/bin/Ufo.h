#pragma once

#include "SceneObject.h"
#include "Reward.h"
#include <fstream>

using uint = unsigned int;

class Ufo : public SceneObject
{
private:
	//States of the UFO
	enum ufoState {OCULTO, VISIBLE, DESTRUIDO};
	//Current state
	ufoState _currentState;
	//Amount of time to change to 'OCULTO' State
	float _occultTime;
	//Current amount of occultTime
	float _currentOccultTime;
	//Min and max time to get the random value
	std::pair<int, int> minMaxOccultTime;
	//Destination and size of the UFO
	SDL_Rect _myRect;
	//Amount of time to render the dead frame
	const float _dieTime = 40;
	//Current dieTime
	float _currentDieTime = 0;
	//Initial position of the UFO
	Vector2D<float> _initialPos;
	//Pointer to reward
	Reward* _reward = nullptr;

public:
	Ufo(GameState* State, PlayState* myPlayState, SDLApplication* app, Vector2D<float> pos, Texture* texture, std::pair<uint, uint> size, int state, float wait);
	Ufo(GameState* State, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture);
	~Ufo();

	//Game States
	void render() const override;
	void update() override;
	void save(std::ostream& out) const override;

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	void updateState();

	//Getter
	Reward* getReward() const { return _reward; };
};

