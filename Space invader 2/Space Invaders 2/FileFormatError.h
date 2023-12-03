#pragma once
#include "InvadersError.h"

class FileFormatError : public InvadersError
{
	FileFormatError(const string& f) : InvadersError("Format of the file " + f + " is wrong.") {};
	virtual ~FileFormatError() {};
};

