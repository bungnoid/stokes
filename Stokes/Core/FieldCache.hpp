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

	static void SetLimitedSize(const Integer32U limitedSize);

public:

	FieldCache(const FieldRef& field);
	virtual ~FieldCache();

	virtual void* PreFetchBlock(const WideString& attributeName, const Vectoriu& blockStartIndex, const Vectoriu& blockEndIndex);
	virtual void* PreFetchSlice(const WideString& attributeName, const Integer32U sliceStartIndex, const Integer32U sliceEndIndex);

	virtual void Flush(void* address);

private:

	static Integer32U sLimitedSize;

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

private:

	FieldRef                       mField;

	std::map<void*, Segement> mSegements;
};

LEAVE_NAMESPACE_STOKES

#endif
