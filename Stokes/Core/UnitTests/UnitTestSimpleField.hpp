#include <cxxtest/TestSuite.h>
                              
#include <Stokes/Core/SimpleField.hpp>

class UnitTestSimpleField : public CxxTest::TestSuite
{
public:
	void setUp()
	{
		Stokes::Matrixf localToWorld;
		localToWorld.data[3] = localToWorld.data[7] = localToWorld.data[11] = -5;
		Stokes::Bound bound(-5, -5, -5, 5, 5, 5);
		Stokes::Vectoriu totalDimension(10, 10, 10);
		Stokes::Integer32 arity = 3;

		mSimpleField.reset(new Stokes::SimpleField(localToWorld, bound, totalDimension, arity));
		std::cout << std::endl;
	}

	void testIndexAndPoint()
	{
		const Stokes::Vectoriu dimension = mSimpleField->GetDimension();

		Stokes::Vectoriu index;
		for (index.x = 0; index.x < dimension.x; ++ index.x)
		{
			for (index.y = 0; index.y < dimension.y; ++ index.y)
			{
				for (index.z = 0; index.z < dimension.z; ++ index.z)
				{
					Stokes::Vectoriu index2;
					const Stokes::Vectorf worldPoint = mSimpleField->CalculateLocalPointFromIndex(index);
					TS_ASSERT(mSimpleField->CalculateIndexFromWorldPoint(worldPoint, index2));
					TS_ASSERT(index == index2);
					std::cout << index << " | " << worldPoint << " | " << index2 << std::endl;
				}
			}
		}
	}

private:

	Stokes::SimpleFieldRef mSimpleField;
};
