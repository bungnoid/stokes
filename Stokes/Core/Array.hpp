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

	virtual Integer64U Resize(const DataType dataType, const Integer64U length) = 0;

	virtual void PreAccess(const Integer64U offset, const Integer32U length = 0) = 0;
	virtual void* Access(const Integer64U offset, const Integer32U length = 0) = 0;
	virtual void PostAccess(const Integer64U offset, const Integer32U length = 0) = 0;

protected:

	DataType mDataType;

	Integer64U mLength;
};

typedef boost::shared_ptr<Array> ArrayRef;

LEAVE_NAMESPACE_STOKES

#endif
