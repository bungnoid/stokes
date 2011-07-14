#ifndef FIELDCACHE_HPP
#define FIELDCACHE_HPP

#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

class Field;

class STOKES_API FieldCache
{
public:

	static Integer32U GetSystemPageSize();

public:

	FieldCache(const Integer32U size);
	virtual ~FieldCache();

	virtual Integer32U PreFetch(const Field& field, const Vectoriu& minElementIndex, const Vectorui& maxElementIndex);

private:

	void**     mAddressesPerThread;
	Integer32U mSize;
};

LEAVE_NAMESPACE_STOKES

#endif
