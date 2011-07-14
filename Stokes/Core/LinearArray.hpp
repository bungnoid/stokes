#ifndef LINEARARRAY_HPP
#define LINEARARRAY_HPP

#include <Stokes/Core/Array.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API LinearArray : public Array
{
public:

	LinearArray(const DataType type, const Integer64U length);
	virtual ~LinearArray();

	virtual Integer64U Resize(const DataType type, const Integer64U length);

	virtual void PreAccess(const Integer64U index);
	virtual void* Access(const Integer64U index);
	virtual void PostAccess(const Integer64U index);

protected:

	void* mAddress;
};

LEAVE_NAMESPACE_STOKES

#endif
