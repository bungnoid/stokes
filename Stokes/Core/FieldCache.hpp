#ifndef FIELDCACHE_HPP
#define FIELDCACHE_HPP

#include <map>

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

	virtual Integer32U PreFetchBlock(const FieldRef& field, const Vectoriu& blockStartIndex, const Vectoriu& blockEndIndex);
	virtual Integer32U PreFetchSlice(const FieldRef& field, const Integer32U sliceStartIndex, const Integer32U sliceEndIndex);

private:

	struct Segement
	{
		Segement(const Integer64U theOffset = 0, const Integer32U theLength = 0, const void* theAddress = NULL) :
			offset(theOffset),
			length(theLength),
			address(const_cast<void*>(theAddress))
		{
		}

		Integer64U offset;
		Integer32U length;
		void*      address;
	};
	std::map<Integer64U, Segement> mSegements;
};

LEAVE_NAMESPACE_STOKES

#endif
