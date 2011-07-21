#include <cxxtest/TestSuite.h>

#include <Stokes/Core/Matrix.hpp>

class UnitTestMatrix : public CxxTest::TestSuite
{
public:

	void setUp()
	{
		A.data[0] = A.data[5] = A.data[10] = 2;
		A.data[3] = A.data[7] = A.data[11] = 2;
	}

	void testTranspose()
	{
		std::cout << std::endl << A << std::endl << Stokes::Transpose(A) << std::endl;
	}

	void testInvert()
	{
		std::cout << std::endl << A << std::endl << Stokes::Invert(A) << std::endl;
	}
	
private:

	Stokes::Matrixf A;
};
