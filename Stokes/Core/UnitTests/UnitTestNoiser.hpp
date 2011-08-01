#include <cxxtest/TestSuite.h>

#include <Stokes/Core/Noiser.hpp>
#include <Stokes/Core/SimpleField.hpp>

class UnitTestNoiser : public CxxTest::TestSuite
{
public:

	UnitTestNoiser() :
	  bound(0, 0, 0, 64, 64, 1),
	  dimension(512, 512, 1),
	  arity(1)
	{
	}
	~UnitTestNoiser()
	{
	}

	void testNoise()
	{
		Stokes::SimpleField noiseField(localToWorld, bound, dimension, arity);
 
		Stokes::Vectoriu index;
		for (index.z = 0; index.z < dimension.z; ++ index.z)
		{
			for (index.y = 0; index.y < dimension.y; ++ index.y)
			{
				for (index.x = 0; index.x < dimension.x; ++ index.x)
				{
					const Stokes::Vectorf localPoint = noiseField.CalculateLocalPointFromIndex(index);
					noiseField.Access(index)[0] = Stokes::Noiser::Noise(localPoint.x, localPoint.y, localPoint.z);
				}
			}
		}

		FILE* fp = fopen("testNoisedField.raw", "wb");
		TS_ASSERT(fp);
		fwrite(noiseField.Access(Stokes::Vectoriu(0, 0, 0)), noiseField.GetSize(), 1, fp);
		fclose(fp);
	}

	void testFBM()
	{
		Stokes::SimpleField fbmField(localToWorld, bound, dimension, arity);

		Stokes::Vectoriu index;
		for (index.z = 0; index.z < dimension.z; ++ index.z)
		{
			for (index.y = 0; index.y < dimension.y; ++ index.y)
			{
				for (index.x = 0; index.x < dimension.x; ++ index.x)
				{
					const Stokes::Vectorf localPoint = fbmField.CalculateLocalPointFromIndex(index);
					fbmField.Access(index)[0] = Stokes::Noiser::FractalBrownianMotion(localPoint, 0.1, 8, 8, 1);
				}
			}
		}

		FILE* fp = fopen("testFBMField.raw", "wb");
		TS_ASSERT(fp);
		fwrite(fbmField.Access(Stokes::Vectoriu(0, 0, 0)), fbmField.GetSize(), 1, fp);
		fclose(fp);
	}
	
	void testTurbulence()
	{
		Stokes::SimpleField turbulenceField(localToWorld, bound, dimension, arity);

		Stokes::Vectoriu index;
		for (index.z = 0; index.z < dimension.z; ++ index.z)
		{
			for (index.y = 0; index.y < dimension.y; ++ index.y)
			{
				for (index.x = 0; index.x < dimension.x; ++ index.x)
				{
					const Stokes::Vectorf localPoint = turbulenceField.CalculateLocalPointFromIndex(index);
					turbulenceField.Access(index)[0] = Stokes::Noiser::Turbulence(localPoint, 8);
				}
			}
		}

		FILE* fp = fopen("testTurbulenceField.raw", "wb");
		TS_ASSERT(fp);
		fwrite(turbulenceField.Access(Stokes::Vectoriu(0, 0, 0)), turbulenceField.GetSize(), 1, fp);
		fclose(fp);
	}

public:

	Stokes::Matrixf localToWorld;
	Stokes::Bound bound;
	Stokes::Vectoriu dimension;
	Stokes::Integer32U arity;
};
