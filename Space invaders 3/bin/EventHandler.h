#pragma once
#include<SDL.h>
#include "checkML.h"
class EventHandler
{
public:
	virtual void manageEvent(const SDL_Event& event) = 0;
};

