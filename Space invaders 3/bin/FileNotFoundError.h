#pragma once
#include "InvadersError.h"

class FileNotFoundError: public InvadersError
{
public:
	FileNotFoundError(const std::string& f) : InvadersError("File " + f + " not found.") {};
	virtual ~FileNotFoundError() {};

	const char* what() override { return e.c_str(); };
};

