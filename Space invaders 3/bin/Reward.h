#pragma once
#include "texture.h"
class Reward
{
private:
	Texture* _myTexture;
	SDL_Rect _myRect;
	const int _velocity;
protected: 
	//Reward() {};
	virtual void rewardBehaviour() = 0/*{_pos -= _velocity}*/;
	virtual void render() const = 0;
	virtual void update() = 0/*{mayGrantReward}*/;
	virtual void onCollision() = 0;
};

