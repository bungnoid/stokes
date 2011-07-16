#include <Stokes/Core/ThreadLocalCache.hpp>

#ifdef STOKES_PLATFORM_WINDOWS
#include <Windows.h>
#endif

ENTER_NAMESPACE_STOKES

Integer32U ThreadLocalCache::sCacheLineSize = 64;
Integer32U ThreadLocalCache::sLimitedSize = 0;

Integer32U ThreadLocalCache::GetSystemPageSize()
{
	Integer32U pageSize = 0;

#ifdef STOKES_PLATFORM_WINDOWS
	SYSTEM_INFO systemInfo;
	memset(&systemInfo, 0, sizeof(SYSTEM_INFO));
	GetSystemInfo(&systemInfo);

	pageSize = systemInfo.dwPageSize;
#endif

	return pageSize;
}

ThreadLocalCache::ThreadLocalCache(const ArrayRef& array) :
	mArray(array)
{
}

ThreadLocalCache::~ThreadLocalCache()
{
}

void* ThreadLocalCache::PreFetch(const Integer64U offset, const Integer32U length)
{
	return NULL;
}

void ThreadLocalCache::Flush()
{
}

LEAVE_NAMESPACE_STOKES
