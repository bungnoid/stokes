#include <Stokes/Core/Field.hpp>
#include <Stokes/Core/FieldCache.hpp>

ENTER_NAMESPACE_STOKES

FieldCache::FieldCache(const Integer32U size)
{
}

FieldCache::~FieldCache()
{
}

Integer32U FieldCache::PreFetchBlock(const FieldRef& field, const Vectoriu& blockStartIndex, const Vectoriu& blockEndIndex)
{
	return 0;
}

Integer32U FieldCache::PreFetchSlice(const FieldRef& field, const Integer32U sliceStartIndex, const Integer32U sliceEndIndex)
{
	return 0;
}

LEAVE_NAMESPACE_STOKES
