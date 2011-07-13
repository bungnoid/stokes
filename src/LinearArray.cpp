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

Integer64U LinearArray::Resize(const DataType mDataType, const Integer64U length)
{
	Integer64U totalSize = GetDataTypeSize(mDataType) * length;
	assert(totalSize != 0);

	mAddress = malloc(totalSize);

	return totalSize;
}

void LinearArray::PreAccess(const Integer64U index)
{
}

void* LinearArray::Access(const Integer64U index)
{
	Integer64U offset = GetDataTypeSize(mDataType) * index;
	return reinterpret_cast<char*>(mAddress) + offset;
}

void LinearArray::PostAccess(const Integer64U index)
{
}

LEAVE_NAMESPACE_STOKES
