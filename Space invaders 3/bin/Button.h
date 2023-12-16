#pragma once
#include "GameObject.h"
#include "EventHandler.h"
#include<functional>
#include "texture.h"
#include "Vector2D.h"
#include "checkML.h"

using CallBack = std::function<void(void)>;

class Button : public GameObject, public EventHandler
{
private:
	Texture* _texture;
	std::list<CallBack> _myCallbacks;
	Point2D<float> _pos;
	std::pair<unsigned int,unsigned int> _rectSize;
public:
	Button(Texture* texture,GameState* gameState, Point2D<float> pos):GameObject(gameState), _texture(texture), _pos(pos) {};
	void connect(CallBack cB);

	void render() const override;
	void update() override {};
	void manageEvent(/*SDL_Event e*/) override {};
	void save(std::ostream& out) const override {};
};

