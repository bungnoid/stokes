#include <memory>

#include <Stokes/Core/LinearArray.hpp>

ENTER_NAMESPACE_STOKES

LinearArray::LinearArray(const DataType dataType, const Integer64U length) :
	Array(dataType, length)
{
	Resize(dataType, length);
}

LinearArray::~LinearArray()
{
}

Integer64U LinearArray::Resize(const DataType dataType, const Integer64U length)
{
	Integer64U oldSize = GetDataTypeSize(mDataType) * mLength;
	Integer64U newSize = GetDataTypeSize(dataType) * length;

	if ((newSize > 0) && (newSize != oldSize))
	{
		free(mAddress);
		mAddress = NULL;
		mAddress = malloc(newSize);
		if (mAddress)
		{
			mDataType = dataType;
			mLength = length;

			return newSize;
		}
	}

	return oldSize;
}

void LinearArray::PreAccess(const Integer64U offset, const Integer32U length)
{
	assert(offset + length <= mLength);
}

void* LinearArray::Access(const Integer64U offset, const Integer32U length)
{
	assert(offset + length <= mLength);

	Integer64U offsetInBytes = GetDataTypeSize(mDataType) * offset;
	return reinterpret_cast<char*>(mAddress) + offsetInBytes;
}

void LinearArray::PostAccess(const Integer64U offset, const Integer32U length)
{
	assert(offset + length <= mLength);
}

LEAVE_NAMESPACE_STOKES
