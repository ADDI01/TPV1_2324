#pragma once
#include "InvadersError.h"

class SDLError: public InvadersError
{
public:
	SDLError(const string& m) : InvadersError("Error de la SDL: " + m) {};
	virtual ~SDLError() {};

	char* what() override {  return what(); };
};

