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
	SDL_Rect _myRect;
	std::pair<unsigned int,unsigned int> _rectSize;
	bool _encima;
public:
	Button();
	Button(Texture* texture,GameState* gameState, Point2D<float> pos, std::pair<unsigned int, unsigned int> size):GameObject(gameState), _texture(texture), _pos(pos),
		_rectSize(size) {
		_myRect.x = _pos.getX();
		_myRect.y = _pos.getY();
		_myRect.h = _rectSize.first;
		_myRect.w = _rectSize.second;
	};
	void connect(CallBack cB);

	void render() const override;
	void update() override; 
	void manageEvent(/*SDL_Event e*/) override {};
	void save(std::ostream& out) const override {};
};

