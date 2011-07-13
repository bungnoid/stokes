#ifndef STOKES_LINEARARRAY_HPP
#define STOKES_LINEARARRAY_HPP

#include <Array.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API LinearArray : public Array
{
public:

	LinearArray(const DataType type, const Integer64U length);
	virtual ~LinearArray();

	virtual Integer64U Resize(const DataType type, const Integer64U length);

	void* GetAddress();

protected:

	void* mAddress;
};

LEAVE_NAMESPACE_STOKES

#endif
