#include <cxxtest/TestSuite.h>

#include <Stokes/Core/LinearArray.hpp>

class UnitTestLinearArray : public CxxTest::TestSuite
{
public:
	void setUp()
	{
	}
	void tearDown()
	{
	}

	void testOverall()
	{
		const Stokes::DataType dataType = Stokes::DATA_TYPE_FLOAT;
		const Stokes::Integer64U length = 128;
		const Stokes::Integer64U size = Stokes::GetDataTypeSize(dataType) * length;

		Stokes::LinearArray testLinearArray(Stokes::DATA_TYPE_FLOAT, 128);

		TS_ASSERT(testLinearArray.GetDataType() == dataType);
		TS_ASSERT(testLinearArray.GetLength() == length);
		TS_ASSERT(testLinearArray.GetSize() == size);
	}
};
