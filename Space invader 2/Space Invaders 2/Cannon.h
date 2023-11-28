#pragma once
#include "SceneObject.h"


class Cannon: public SceneObject
{
private:
	//Cannon's direction
	Vector2D<float> _direction;
	//Cannon's speed
	float _velocity = 0;
	//Cannon's shoot cooldown
	float _shootCD = 0;
	float _iniShootCD = 0;
	//Destination and size of the cannon
	SDL_Rect* _myRect = nullptr;

public:
	Cannon(Point2D<float> pos, Texture* texture, pair<uint, uint> size, Game* game, uint nLifes, float shootCD,
		float velocity) : SceneObject(game, texture, pos, size, nLifes), _shootCD(shootCD), _velocity(velocity) {
		_myRect = new SDL_Rect; _iniShootCD = shootCD;
	};
	~Cannon();

	//Game states
	void render() const override;
	bool update() override;
	void handleEvents(const SDL_Event& event);
	bool save() const override { return true; };

	//Specific actions
	bool hit(SDL_Rect AttackRect, int typeOfDamage) override;
	bool canShoot() const;

	//Setters
	void setCoolDown(float coolDown) { _shootCD = coolDown; };

	//Getters
	Vector2D<float> getPosition() const { return _pos; };
	SDL_Rect* getRect() const { return _myRect; };
};

