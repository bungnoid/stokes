#include <fstream>

#include <cxxtest/TestSuite.h>

#include <Stokes/Core/DenseMappedField.hpp>

class UnitTestDenseMappedField : public CxxTest::TestSuite
{
public:

	void testOverall()
	{
		// Fill dense array with numbers.
		const Stokes::Matrixf localToWorldMatrix;
		const Stokes::Bound bound(0, 0, 0, 512, 512, 64);
		const Stokes::Vectoriu dimension(512, 512, 64);
		const Stokes::Vectori64u dimension64(dimension.x, dimension.y, dimension.z);
		const Stokes::Integer32U arity = 4;
		const Stokes::Integer32U pagedSliceCount = 16;

		const Stokes::WideString path(L"testDenseMappedField.dat");

		mTestDenseMappedField.reset(new Stokes::DenseMappedField(localToWorldMatrix, bound, dimension, arity, pagedSliceCount));
		TS_ASSERT(mTestDenseMappedField);

		Stokes::FileMappingRef fileMapping = mTestDenseMappedField->GetFileMapping();
		TS_ASSERT(fileMapping->Open(path, Stokes::FileMapping::MAPPING_MODE_READ_WRITE, mTestDenseMappedField->GetSize()));

		Stokes::Vectoriu index;
		for (index.z = 0; index.z < dimension64.z; ++ index.z)
		{
			for (index.y = 0; index.y < dimension64.y; ++ index.y)
			{
				for (index.x = 0; index.x < dimension64.x; ++ index.x)
				{
					const Stokes::Integer64U linearIndex = dimension64.x * dimension64.y * index.z + dimension64.x * index.y + index.x;
					Stokes::Float* element = mTestDenseMappedField->Access(index);
					element[0] = element[1] = element[2] = element[3] = static_cast<Stokes::Float>(linearIndex);
				}
			}
		}

		mTestDenseMappedField.reset();

		// Verify data.
		FILE* fp = _wfopen(path.c_str(), L"rb");
		TS_ASSERT(fp);
		
		for (Stokes::Integer64U i = 0; i < dimension64.x * dimension64.y * dimension64.z; ++i)
		{
			Stokes::Float element[arity];
			fread(element, sizeof(Stokes::Float), arity, fp);

			TS_ASSERT(element[0] == i);
			TS_ASSERT(element[1] == i);
			TS_ASSERT(element[2] == i);
			TS_ASSERT(element[3] == i);
		}
		fclose(fp);

		// Remove file.
		_wremove(path.c_str());
	}

private:

	Stokes::DenseMappedFieldRef mTestDenseMappedField;
};
