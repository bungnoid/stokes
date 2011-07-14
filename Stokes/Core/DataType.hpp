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
	DATATYPE_INTEGER32,
	DATATYPE_INTEGER32U,
	
	DATATYPE_INTEGER64,
	DATATYPE_INTEGER64U,

	DATATYPE_HALF,
	DATATYPE_REAL,
	DATATYPE_DOUBLE,
};

STOKES_API Integer32U GetDataTypeSize(const DataType dataType);

LEAVE_NAMESPACE_STOKES

#endif
