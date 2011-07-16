#include <cxxtest/TestSuite.h>

#include <Stokes/Core/Field.hpp>
#include <Stokes/Core/MappedArray.hpp>

class UnitTestField : public CxxTest::TestSuite
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
		const Stokes::WideString testFieldName(L"testFieldName");
		const Stokes::Bound bound(0, 0, 0, 8, 8, 8);
		const Stokes::Vectoriu globalDim(9, 9, 9);
		const Stokes::Vectoriu newGlobalDim(10, 10, 10);
		const Stokes::Vectoriu blockDim(2, 2, 2);

		Stokes::FieldRef testField(new Stokes::Field(testFieldName, bound, globalDim, blockDim));
		TS_ASSERT(testField->GetName() == testFieldName);
		TS_ASSERT(testField->GetStorageMode() == Stokes::Field::STORAGE_BLOCK);
		TS_ASSERT(testField->GetGlobalDim() == newGlobalDim);
		TS_ASSERT(testField->GetBlockDim() == blockDim);

		for (Stokes::Integer32U k = 0; k < newGlobalDim.z; ++ k)
		{
			for (Stokes::Integer32U j = 0; j < newGlobalDim.y; ++ j)
			{
				for (Stokes::Integer32U i = 0; i < newGlobalDim.x; ++ i)
				{
					std::cout << testField->ConvertGlobalIndexToWorldPosition(Stokes::Vectoriu(i, j, k)) << '\t' << Stokes::Vectorf(i + 0.5f, j + 0.5f, k + 0.5f);
				}
			}
		}


		const Stokes::WideString pathToTestDensityMappedArray(L"testDensityMappedArray.dat");

		Stokes::MappedArray* testDensityMappedArray = new Stokes::MappedArray(Stokes::DATA_TYPE_FLOAT, Stokes::MappedArray::MAPPING_MODE_READ_WRITE);
		TS_ASSERT(testDensityMappedArray->OpenMappedFile(pathToTestDensityMappedArray));
		TS_ASSERT(testDensityMappedArray->Resize(newGlobalDim.x * newGlobalDim.y * newGlobalDim.z) == newGlobalDim.x * newGlobalDim.y * newGlobalDim.z * Stokes::GetDataTypeSize(Stokes::DATA_TYPE_FLOAT));

		const Stokes::WideString semanticDensityAlias(L"semanticDensityAlias");
		testField->Bind(Stokes::Field::SEMANTIC_DENSITY, semanticDensityAlias, Stokes::ArrayRef(testDensityMappedArray));

		Stokes::WideString semanticName;
		Stokes::ArrayRef semanticArray;
		TS_ASSERT(testField->GetBinding(Stokes::Field::SEMANTIC_DENSITY, semanticName, semanticArray));
		TS_ASSERT(semanticName == semanticDensityAlias);
		TS_ASSERT(semanticArray.get() == testDensityMappedArray);
	}
};
