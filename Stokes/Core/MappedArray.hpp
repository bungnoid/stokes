#ifndef MAPPEDARRAY_HPP
#define MAPPEDARRAY_HPP

#include <string>

#include <Stokes/Core/LinearArray.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API MappedArray : public Array
{
public:

	enum MappingMode
	{
		MAPPING_MODE_READ_ONLY,
		MAPPING_MODE_READ_WRITE
	};

	MappedArray(const DataType dataType, const MappingMode mappingMode);
	virtual ~MappedArray();

	/**
	 * Open an exsit file to read or create a new file.
	 */
	bool OpenMappedFile(const WideString& pathToMappedFile);
	const WideString& GetPathToMappedFile() const;
	MappingMode GetMappingMode() const;

	virtual Integer64U Resize(const Integer64U length);

	virtual void* Access(const Integer64U offset, const Integer32U length);
	virtual void Flush(void* address);

private:

	WideString mPathToMappedFile;

	MappingMode mMappingMode;

	int mMappedFile;
};

LEAVE_NAMESPACE_STOKES

#endif
