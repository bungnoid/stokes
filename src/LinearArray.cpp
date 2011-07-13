#include <memory>

#include <LinearArray.hpp>

ENTER_NAMESPACE_STOKES

LinearArray::LinearArray(const DataType dataType, const Integer64U length) :
	Array(dataType, length)
{
}

LinearArray::~LinearArray()
{
}

Integer64U LinearArray::Resize(const DataType type, const Integer64U length)
{
	Integer64U totalSize = GetDataTypeSize(type) * length;
	assert(totalSize != 0);

	mAddress = malloc(totalSize);

	return totalSize;
}

void* LinearArray::GetAddress()
{
	return mAddress;
}

LEAVE_NAMESPACE_STOKES
