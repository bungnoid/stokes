#ifndef STOKES_ARRAY_HPP
#define STOKES_ARRAY_HPP

#include <cassert>

#include <API.hpp>
#include <DataType.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Array
{
public:

	Array(const DataType dataType, const Integer64U length);
	virtual ~Array();

	DataType GetDataType() const;

	Integer64U GetLength() const;

	virtual Integer64U Resize(const DataType dataType, const Integer64U length) = 0;

protected:

	DataType mDataType;

	Integer64U mLength;
};

LEAVE_NAMESPACE_STOKES

#endif
