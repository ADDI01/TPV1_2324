#pragma once

#include <stdexcept>

using namespace std;

class InvadersError: public logic_error
{
protected:
	InvadersError(const char* & err) : logic_error(err) {};
	virtual ~InvadersError() {};

	virtual string what() = 0;
};

