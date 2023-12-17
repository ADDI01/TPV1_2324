#pragma once
#include<SDL.h>
class EventHandler
{
public:
	virtual void manageEvent(const SDL_Event& event) = 0;
};

