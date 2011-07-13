#ifndef TYPE_HPP
#define TYPE_HPP

#include <API.hpp>

ENTER_NAMESPACE_STOKES

typedef int Integer32;
typedef unsigned int Integer32U;

typedef long long Integer64;
typedef unsigned long long Integer64U;

typedef float Float;
typedef double Double;

enum DataType
{
	STOKES_DATATYPE_NONE = 0,

	STOKES_DATATYPE_INTEGER32,
	STOKES_DATATYPE_INTEGER32U,
	
	STOKES_DATATYPE_INTEGER64,
	STOKES_DATATYPE_INTEGER64U,

	STOKES_DATATYPE_HALF,
	STOKES_DATATYPE_REAL,
	STOKES_DATATYPE_DOUBLE,
};

STOKES_API Integer32U GetDataTypeSize(const DataType dataType);

LEAVE_NAMESPACE_STOKES

#endif
