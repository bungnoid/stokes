#include <memory>

#include <Stokes/Core/LinearArray.hpp>

ENTER_NAMESPACE_STOKES

LinearArray::LinearArray(const DataType dataType, const Integer64U length) :
	Array(dataType, length),
	mAddress(NULL)
{
	Resize(length);
}

LinearArray::~LinearArray()
{
}

Integer64U LinearArray::Resize(const Integer64U length)
{
	Integer32U dataTypeSize = GetDataTypeSize(mDataType);
	Integer64U oldSize = dataTypeSize * mLength;
	Integer64U newSize = dataTypeSize * length;

	if (newSize != oldSize)
	{
		if (mAddress)
		{
			free(mAddress);
			mAddress = NULL;
		}

		if (newSize > 0)
		{
			free(mAddress);
			mAddress = NULL;
			mAddress = malloc(newSize);
			if (mAddress)
			{
				mLength = length;

				memset(mAddress, 0, newSize);

				return newSize;
			}
		}

	}

	return oldSize;
}

void* LinearArray::Access(const Integer64U offset, const Integer32U length)
{
	assert(offset + length <= mLength);

	Integer64U offsetInBytes = GetDataTypeSize(mDataType) * offset;
	return reinterpret_cast<char*>(mAddress) + offsetInBytes;
}

void LinearArray::Flush(void* address)
{
	assert(address >= mAddress);
}

LEAVE_NAMESPACE_STOKES
