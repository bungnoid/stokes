#ifndef THREADLOCALCACHE_HPP
#define THREADLOCALCACHE_HPP

#include <map>

#include <Stokes/Core/Array.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API ThreadLocalCache
{
public:

	static Integer32U GetSystemPageSize();

	static void SetCacheLineSize(const Integer32U cacheLineSize);

	static void SetLimitedSize(const Integer32U limitedLineSize);

public:

	ThreadLocalCache(const ArrayRef& array);
	virtual ~ThreadLocalCache();

	virtual void* PreFetch(const Integer64U offset, const Integer32U length);

	virtual void Flush();

private:

	static Integer32U sLimitedSize;

	static Integer32U sCacheLineSize;

protected:

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

protected:

	ArrayRef                  mArray;

	std::map<void*, Segement> mSegements;
};

LEAVE_NAMESPACE_STOKES

#endif
