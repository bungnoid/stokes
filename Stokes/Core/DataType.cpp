#include <Stokes/Core/DataType.hpp>

ENTER_NAMESPACE_STOKES

Integer32U GetDataTypeSize(const DataType dataType)
{
	switch(dataType)
	{
		case DATATYPE_HALF:
			return 2;

		case DATATYPE_INTEGER32:
		case DATATYPE_INTEGER32U:
		case DATATYPE_REAL:
			return 4;

		case DATATYPE_INTEGER64:
		case DATATYPE_INTEGER64U:
		case DATATYPE_DOUBLE:
			return 8;
	}

	return 0;
}

LEAVE_NAMESPACE_STOKES
