#pragma once
#include "InvadersError.h"

class FileNotFoundError: public InvadersError
{
public:
	FileNotFoundError(const string& f) : InvadersError("File " + f + " not found.") {};
	virtual ~FileNotFoundError() {};
};

