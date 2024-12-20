#pragma once
#include "texture.h"
#include "SceneObject.h"
#include "checkML.h"

class Bomb : public SceneObject
{
private:
	SDL_Rect _myRect;
	Vector2D<float> _velocity;
	//Defines the father. 
	Father _father;

public:
	Bomb(GameState* game, PlayState* myPlayState, SDLApplication* app,
		SDL_Renderer* renderer, Texture* texture, Point2D<float>pos, std::pair<uint, uint> size, Vector2D<float> velocity,
		Father father);
	//virtual void rewardBehaviour() /*{_pos -= _velocity}*/;

	virtual void render() const;
	virtual void update() /*{mayGrantReward}*/;
	void save(std::ostream& out) const override {};
	void bombBehaviour(CallBack cB);
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	SDL_Rect getRect() const { return _myRect; };
};

