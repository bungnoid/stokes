#ifndef DATATYPE_HPP
#define DATATYPE_HPP

#include <string>

#include <Stokes/Core/API.hpp>

ENTER_NAMESPACE_STOKES

typedef int                Integer32;
typedef unsigned int       Integer32U;

typedef long long          Integer64;
typedef unsigned long long Integer64U;

typedef float              Float;
typedef double             Double;

typedef std::string        CharString;
typedef std::wstring       WideString;

enum DataType
{
	DATA_TYPE_INTEGER32,
	DATA_TYPE_INTEGER32U,
	
	DATA_TYPE_INTEGER64,
	DATA_TYPE_INTEGER64U,

	DATA_TYPE_HALF,
	DATA_TYPE_FLOAT,
	DATA_TYPE_DOUBLE,
};

struct Address
{
	Address(void* raw = NULL) :
		theRaw(raw)
	{
	}

	union
	{
		Integer32  *theInteger32;
		Integer32U *theInteger32U;

		Integer64  *theInteger64;
		Integer64U *theInteger64U;

		Float      *theFloat;
		Double     *theDouble;

		void       *theRaw;
	};
};


STOKES_API Integer32U GetDataTypeSize(const DataType dataType);

LEAVE_NAMESPACE_STOKES

#endif
