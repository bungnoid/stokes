#include <Stokes/Core/Field.hpp>
#include <Stokes/Core/FieldCache.hpp>

#ifdef STOKES_PLATFORM_WINDOWS
#include <Windows.h>
#endif

ENTER_NAMESPACE_STOKES

Integer32U FieldCache::sLimitedSize = 0;

Integer32U FieldCache::GetSystemPageSize()
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

FieldCache::FieldCache(const FieldRef& field, const Integer32U limitedSize) :
	mField(field)
{
}

FieldCache::~FieldCache()
{
}

void* FieldCache::PreFetchBlock(const WideString& attributeName, const Vectoriu& blockStartIndex, const Vectoriu& blockEndIndex)
{
	if (mField->GetStorageMode() == Field::STORAGE_BLOCK)
	{
	}

	return NULL;
}

void* FieldCache::PreFetchSlice(const WideString& attributeName, const Integer32U sliceStartIndex, const Integer32U sliceEndIndex)
{
	if (mField->GetStorageMode() == Field::STORAGE_SLICE)
	{
		Field::SemanticType semanticType;
		ArrayRef array;
		if (mField->QueryAttribute(attributeName, semanticType, array))
		{
			assert(array);

			const Vectoriu& totalDim = mField->GetTotalDim();
			const Integer32U arity = Field::GetSemanticTypeArity(semanticType);
			const Integer64U offset = totalDim.x * totalDim.y * sliceStartIndex * arity;
			const Integer32U length = totalDim.x * totalDim.y * (sliceEndIndex - sliceStartIndex) * arity;
			const Integer32U size = length * GetDataTypeSize(array->GetDataType());

			array->PreAccess(offset, length);
			array->Access(offset, length);
			array->PostAccess(offset, length);
		}
	}

	return NULL;
}

void FieldCache::Flush(void* address)
{

}

LEAVE_NAMESPACE_STOKES
