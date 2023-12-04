#pragma once
#include "InvadersError.h"

class SDLError: public InvadersError
{
public:
	SDLError(const string& m) : InvadersError("Error de la SDL: " + m) {};
	virtual ~SDLError() {};

	const char* what() override { return e.c_str(); };
};