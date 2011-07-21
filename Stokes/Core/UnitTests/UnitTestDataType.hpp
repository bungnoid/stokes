#include <cxxtest/TestSuite.h>
                              
#include <Stokes/Core/DataType.hpp>

class UnitTestDataType : public CxxTest::TestSuite
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
		TS_ASSERT(sizeof(Stokes::Integer32) == 4);
		TS_ASSERT(sizeof(Stokes::Integer32U) == 4);

		TS_ASSERT(sizeof(Stokes::Integer64) == 8);
		TS_ASSERT(sizeof(Stokes::Integer64U) == 8);

		TS_ASSERT(sizeof(Stokes::Char) == 1);
#ifdef STOKES_PLATFORM_WINDOWS
		TS_ASSERT(sizeof(Stokes::WChar) == 2);
#elif STOKES_PLATFORM_POSIX
		TS_ASSERT(sizeof(Stokes::WChar) == 4);
#endif
	}
};
