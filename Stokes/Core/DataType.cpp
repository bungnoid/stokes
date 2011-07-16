#include <Stokes/Core/DataType.hpp>

ENTER_NAMESPACE_STOKES

Integer32U GetDataTypeSize(const DataType dataType)
{
	switch(dataType)
	{
		case DATA_TYPE_HALF:
			return 2;

		case DATA_TYPE_INTEGER32:
		case DATA_TYPE_INTEGER32U:
		case DATA_TYPE_FLOAT:
			return 4;

		case DATA_TYPE_INTEGER64:
		case DATA_TYPE_INTEGER64U:
			return 8;
	}

	return 0;
}

LEAVE_NAMESPACE_STOKES
