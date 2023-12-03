#pragma once

#include <stdexcept>

using namespace std;

class InvadersError: public logic_error
{
protected:
	InvadersError(const string& err) : logic_error(err) {};
	virtual ~InvadersError() {};

	virtual char* what() = 0;
};

