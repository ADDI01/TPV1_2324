#pragma once
#include "InvadersError.h"

class FileFormatError : public InvadersError
{
public:
	FileFormatError(const string& f) : InvadersError("Format of the file " + f + " is wrong.") {};
	virtual ~FileFormatError() {};

	char* what() override { return what(); };
};

