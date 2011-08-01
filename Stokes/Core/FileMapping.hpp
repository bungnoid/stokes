#ifndef STOKES_CORE_FILEMAPPING_HPP
#define STOKES_CORE_FILEMAPPING_HPP

#include <Stokes/Core/DataType.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API FileMapping
{
public:

	static Integer32U GetSystemPageSize();

public:

	enum MappingMode
	{
		MAPPING_MODE_READ,
		MAPPING_MODE_READ_WRITE
	};

	FileMapping();
	~FileMapping();

	bool Open(const WideString& path, const MappingMode mappingMode, const Integer64U size);

	void* MapToSwapFile(const Integer64U offset, const Integer32U size);
	void UnMapFromSwapFile(const void* address, const Integer32U size);

private:

	WideString  mPath;

	MappingMode mMappingMode;

	int         mFile;
};

typedef boost::shared_ptr<FileMapping> FileMappingRef;

LEAVE_NAMESPACE_STOKES

#endif
