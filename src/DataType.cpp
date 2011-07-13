#include <DataType.hpp>

ENTER_NAMESPACE_STOKES

Integer32U GetDataTypeSize(const DataType dataType)
{
	switch(dataType)
	{
		case STOKES_DATATYPE_HALF:
			return 2;

		case STOKES_DATATYPE_INTEGER32:
		case STOKES_DATATYPE_INTEGER32U:
		case STOKES_DATATYPE_REAL:
			return 4;

		case STOKES_DATATYPE_INTEGER64:
		case STOKES_DATATYPE_INTEGER64U:
		case STOKES_DATATYPE_DOUBLE:
			return 8;
	}

	return 0;
}

LEAVE_NAMESPACE_STOKES
