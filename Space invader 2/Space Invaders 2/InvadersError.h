#pragma once

#include <stdexcept>

using namespace std;

class InvadersError: public logic_error
{
protected:
	string e;
	InvadersError(const string& err) : logic_error(err), e(err) {};
	virtual ~InvadersError() {};

	virtual const char* what() = 0;
};

