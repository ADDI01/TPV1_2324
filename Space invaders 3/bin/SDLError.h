#pragma once
#include "InvadersError.h"
#include "checkML.h"

class SDLError: public InvadersError
{
public:
	SDLError(const std::string& m) : InvadersError("Error de la SDL: " + m) {};
	virtual ~SDLError() {};

	const char* what() override { return e.c_str(); };
};