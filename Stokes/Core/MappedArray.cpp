#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Stokes/Core/MappedArray.hpp>

#include <Windows.h>

ENTER_NAMESPACE_STOKES

Integer32U MappedArray::sCacheSize = 0;

Integer32U MappedArray::GetCacheSize()
{
	return sCacheSize;
}

void MappedArray::SetCacheLength(const Integer32U cacheSize)
{
	sCacheSize = cacheSize;
}

MappedArray::MappedArray(const WideString& pathToMappedFile, const DataType dataType, const Integer64U length) :
	LinearArray(dataType, length),
	mPathToMappedFile(pathToMappedFile),
	mMappedFile(-1)
{
	Resize(dataType, length);
}

MappedArray::~MappedArray()
{
	HANDLE hFileMapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, mPathToMappedFile.c_str());
	if (hFileMapping != INVALID_HANDLE_VALUE)
	{
		if (CloseHandle(hFileMapping) == TRUE)
		{
			_close(mMappedFile);
		}
	}
}

const WideString& MappedArray::GetPathToMappedFile() const
{
	return mPathToMappedFile;
}

Integer64U MappedArray::Resize(const DataType dataType, const Integer64U length)
{
	errno_t failed = _wsopen_s(&mMappedFile, mPathToMappedFile.c_str(), _O_BINARY|_O_CREAT|_O_EXCL|_O_RDWR, _SH_DENYNO, _S_IREAD|_S_IWRITE);
	if (failed == 0)
	{
		assert(mMappedFile != -1); 

		HANDLE hMappedFile = reinterpret_cast<HANDLE>(_get_osfhandle(mMappedFile));
		assert(hMappedFile != INVALID_HANDLE_VALUE);

		LARGE_INTEGER fileSize;
		fileSize.QuadPart = GetDataTypeSize(dataType) * length;

		if (::SetFilePointerEx(hMappedFile, fileSize, NULL, FILE_BEGIN))
		{
			::SetEndOfFile(hMappedFile);

			HANDLE hFileMapping = ::CreateFileMappingW(hMappedFile, NULL, PAGE_READWRITE, fileSize.HighPart, fileSize.LowPart, mPathToMappedFile.c_str());
			assert(hFileMapping != INVALID_HANDLE_VALUE);
		}

		return fileSize.QuadPart;
	}

	return 0;
}

void MappedArray::PreAccess(const Integer64U index)
{
	void* cache = LinearArray::Access(0);

	HANDLE hFileMapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, mPathToMappedFile.c_str());
	MapViewOfFileEx(hFileMapping, FILE_MAP_ALL_ACCESS, 0, GetCacheSize(), GetDataTypeSize(mDataType) * index, cache);
}

void* MappedArray::Access(const Integer64U index)
{
	return LinearArray::Access(index);
}

void MappedArray::PostAccess(const Integer64U index)
{
	void* cache = LinearArray::Access(0);

	UnmapViewOfFile(cache);
}

LEAVE_NAMESPACE_STOKES
