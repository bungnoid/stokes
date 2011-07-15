#include <cxxtest/TestSuite.h>

#include <Stokes/Core/MappedArray.hpp>

class MappedArrayUnitTest : public CxxTest::TestSuite
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
		const Stokes::WideString pathToMappedFile(L"testMappedArray.dat");
		const Stokes::MappedArray::MappingMode mappingMode = Stokes::MappedArray::MAPPING_MODE_READ_WRITE;
		const Stokes::DataType dataType = Stokes::DATATYPE_INTEGER32;
		const Stokes::Integer64U length = 2 * 2 * 2 * 2 * 2 * 2;
		const Stokes::Integer64U size = Stokes::GetDataTypeSize(dataType) * length;

		// Remove the test file if it exist.
		 _wremove(pathToMappedFile.c_str());

		// Create a 128 bytes file.
		std::auto_ptr<Stokes::MappedArray> testMappedArray(new Stokes::MappedArray(dataType, mappingMode));

		TS_ASSERT(testMappedArray->GetDataType() == dataType);
		TS_ASSERT(testMappedArray->GetLength() == 0);
		TS_ASSERT(testMappedArray->GetSize() == 0);
		TS_ASSERT(testMappedArray->GetPathToMappedFile().size() == 0);
		TS_ASSERT(testMappedArray->GetMappingMode() == mappingMode);

		TS_ASSERT(testMappedArray->OpenMappedFile(pathToMappedFile));
		TS_ASSERT(testMappedArray->Resize(length) == size);
		TS_ASSERT(testMappedArray->GetSize() == size);

		// Write some data.
		const Stokes::Integer64U halfLength = length / 2;
		Stokes::Address address(testMappedArray->Access(0, halfLength));
		std::fill_n(address.theInteger32, halfLength, 1);
		testMappedArray->Flush(address.theRaw);

		address.theRaw = testMappedArray->Access(0, length);
		for (Stokes::Integer64U i =0; i < length; ++ i)
		{
			address.theInteger32[i] += 1;
		}
		testMappedArray->Flush(address.theRaw);

		// Delete the testMappedArray.
		testMappedArray.reset();
	}
};
