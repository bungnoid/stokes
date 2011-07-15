#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <boost/shared_ptr.hpp>

#include <Stokes/Core/DataType.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Array
{
public:

	Array(const DataType dataType, const Integer64U length = 0);
	virtual ~Array();

	DataType GetDataType() const;

	Integer64U GetLength() const;

	Integer64U GetSize() const;

	/**
	 * @param length Re-allocate the array, if length = 0, clear all. 
	 */
	virtual Integer64U Resize(const Integer64U length) = 0;

	virtual void* Access(const Integer64U offset, const Integer32U length) = 0;
	virtual void Flush(void* address) = 0;

protected:

	DataType mDataType;

	Integer64U mLength;
};

typedef boost::shared_ptr<Array> ArrayRef;

LEAVE_NAMESPACE_STOKES

#endif
