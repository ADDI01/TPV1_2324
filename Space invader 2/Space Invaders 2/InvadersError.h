#pragma once

#include <stdexcept>

class InvadersError: public std::logic_error
{
protected:
	std::string e;
	InvadersError(const std::string& err) : std::logic_error(err), e(err) {};
	virtual ~InvadersError() {};

	virtual const char* what() = 0;
};

