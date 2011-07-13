#ifndef STOKES_EXCEPTION_HPP
#define STOKES_EXCEPTION_HPP

#include <exception>

#include <API.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Exception : public std::exception
{
public:
	virtual const char* what() const throw() = 0;
};

LEAVE_NAMESPACE_STOKES

#endif
