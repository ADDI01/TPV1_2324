#pragma once
#include "SceneObject.h"
#include "Laser.h"
#include "EventHandler.h"

class Cannon: public SceneObject, public EventHandler
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
	Cannon(Point2D<float> pos, Texture* texture, std::pair<uint, uint> size, GameState* game, PlayState* myPlayState, SDLApplication* app,
		uint nLifes, float shootCD,
		float velocity);
	Cannon(GameState* game, PlayState* myPlayState, SDLApplication* app, std::ifstream& in, Texture* texture, float velocity);
	~Cannon();

	//Game states
	void render() const override;
	void update() override;
	void manageEvent(const SDL_Event& event) override;
	void save(std::ostream& out) const override ;

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