#include <Stokes/Core/Field.hpp>
#include <Stokes/Core/FieldCache.hpp>

ENTER_NAMESPACE_STOKES

FieldCache::FieldCache(const Integer32U size)
{
}

FieldCache::~FieldCache()
{
}

Integer32U FieldCache::PreFetch(const FieldRef& field, const Vectoriu& minElementIndex, const Vectoriu& maxElementIndex)
{
	return 0;
}

LEAVE_NAMESPACE_STOKES
