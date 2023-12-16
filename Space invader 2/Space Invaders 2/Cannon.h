#pragma once
#include "SceneObject.h"

class Cannon: public SceneObject
{
private:
	//Cannon's direction
	Vector2D<float> _direction;
	//Cannon's speed
	float _velocity = 0;
	//Cannon's initial shoot cooldown and game cooldown
	float  _iniShootCD = 30, _shootCD = 0;
	//Destination and size of the cannon
	SDL_Rect _myRect;

public:
	Cannon(Point2D<float> pos, Texture* texture, std::pair<uint, uint> size, Game* game, uint nLifes, float shootCD,
		float velocity);
	Cannon(Game* game, std::ifstream& in, Texture* texture, float velocity);
	~Cannon();

	//Game states
	void render() const override;
	void update() override;
	void handleEvents(const SDL_Event& event, SDL_Renderer* renderer);
	void save(std::ostream& out) const override;

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	void fireLaser(SDL_Renderer* renderer);
	bool canShoot() const;

	//Setters
	void setCoolDown(float coolDown) { _shootCD = coolDown; };

	//Getters
	Vector2D<float> getPosition() const { return _pos; };
	SDL_Rect getRect() const { return _myRect; };
	uint getnLifes() const { return _life; };
};

