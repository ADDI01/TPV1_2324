#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "checkML.h"
#include "SceneObject.h"

using uint = unsigned int;

class Game;

class Bunker : public SceneObject
{
private:
	//Destination and size of the bunker
	SDL_Rect _myRect;

public:
	Bunker(Point2D<float> pos, Texture* texture, std::pair<uint, uint> size, Game* game, uint nLifes);
	Bunker(Game* game, std::ifstream& in, Texture* texture);
	~Bunker() {};

	//Game states
	void render() const override;
	void update() override;
	void save(std::ostream& out) const override;

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;

	//Getters
	SDL_Rect getRect() const { return _myRect; };
};


