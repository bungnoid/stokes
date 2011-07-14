#include <cassert>

#include <Stokes/Core/Array.hpp>

ENTER_NAMESPACE_STOKES

Array::Array(const DataType dataType, const Integer64U length) :
	mDataType(dataType),
	mLength(length)
{
}

Array::~Array()
{
}

DataType Array::GetDataType() const
{
	return mDataType;
}

Integer64U Array::GetLength() const
{
	return mLength;
}

LEAVE_NAMESPACE_STOKES
