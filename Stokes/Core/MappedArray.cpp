#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Stokes/Core/MappedArray.hpp>

#include <Windows.h>

ENTER_NAMESPACE_STOKES

MappedArray::MappedArray(const WideString& pathToMappedFile, const DataType dataType, const Integer64U length) :
	LinearArray(dataType),
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

			mDataType = dataType;
			mLength = length;

			return fileSize.QuadPart;
		}
	}

	return 0;
}

void MappedArray::PreAccess(const Integer64U offset, const Integer32U length)
{
	LinearArray::Resize(mDataType, length);
}

void* MappedArray::Access(const Integer64U offset, const Integer32U length)
{
	ULARGE_INTEGER offsetInFile;
	offsetInFile.QuadPart = offset;

	HANDLE hFileMapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, mPathToMappedFile.c_str());
	MapViewOfFileEx(hFileMapping, FILE_MAP_ALL_ACCESS, offsetInFile.HighPart, offsetInFile.LowPart, GetDataTypeSize(mDataType) * length, LinearArray::Access(0));
	return LinearArray::Access(0);
}

void MappedArray::PostAccess(const Integer64U offset, const Integer32U length)
{
	UnmapViewOfFile(LinearArray::Access(0));
}

LEAVE_NAMESPACE_STOKES
