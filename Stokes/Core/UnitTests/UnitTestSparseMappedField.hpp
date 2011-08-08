#include <cxxtest/TestSuite.h>

#include <Stokes/Core/SparseMappedField.hpp>

class UnitTestSparseMappedField : public CxxTest::TestSuite
{
public:

	void testOverall()
	{
		const Stokes::Matrixf localToWorld;
		const Stokes::Bound bound(0, 0, 0, 64, 64, 64);
		const Stokes::Vectoriu dimension(64, 64, 64);
		const Stokes::Vectori64u dimension64(dimension.x, dimension.y, dimension.z);
		const Stokes::Integer32U arity = 4;
		const Stokes::Integer32U blockDimension = 32;
		const Stokes::Integer32U pagedBlockCount = dimension.x * dimension.y / blockDimension / blockDimension;

		const Stokes::WideString path(L"testSparseMappedField.raw");

		Stokes::SparseMappedFieldRef testSparseMappedField(new Stokes::SparseMappedField(localToWorld, bound, dimension, arity, pagedBlockCount, blockDimension));
		TS_ASSERT(testSparseMappedField);

		Stokes::FileRef file = testSparseMappedField->GetFile();
		TS_ASSERT(file->Open(path, Stokes::File::ACCESS_MODE_WRITE));
		TS_ASSERT(file->Resize(testSparseMappedField->GetSize()));

		Stokes::Vectoriu index;
		for (index.z = 0; index.z < dimension.z; ++ index.z)
		{
			for (index.y = 0; index.y < dimension.y; ++ index.y)
			{
				for (index.x = 0; index.x < dimension.x; ++ index.x)
				{
					Stokes::Float* element = testSparseMappedField->Access(index);
					TS_ASSERT(element);
					element[0] = static_cast<Stokes::Float>(index.x);
					element[1] = static_cast<Stokes::Float>(index.y);
					element[2] = static_cast<Stokes::Float>(index.z);
					element[3] = 0;;
				}
			}
		}

		_wremove(path.c_str());
	}
};
