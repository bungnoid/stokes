#ifndef LINEARARRAY_HPP
#define LINEARARRAY_HPP

#include <Stokes/Core/Array.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API LinearArray : public Array
{
public:

	LinearArray(const DataType type, const Integer64U length = 0);
	virtual ~LinearArray();

	virtual Integer64U Resize(const Integer64U length);

	virtual void* Access(const Integer64U offset, const Integer32U length);
	virtual void Flush(void* address);

protected:

	void* mAddress;
};

LEAVE_NAMESPACE_STOKES

#endif
