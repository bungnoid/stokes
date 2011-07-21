#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Windows.h>

#include <Stokes/Core/FileMapping.hpp>

ENTER_NAMESPACE_STOKES

#ifdef STOKES_PLATFORM_WINDOWS

Integer32U FileMapping::GetSystemPageSize()
{
	SYSTEM_INFO systemInfo;
	memset(&systemInfo, 0, sizeof(SYSTEM_INFO));
	GetSystemInfo(&systemInfo);
	return systemInfo.dwPageSize;
}

FileMapping::FileMapping() :
	mFile(-1)
{
}

FileMapping::~FileMapping()
{
	if (mFile != -1)
	{

		DWORD desiredAccess = (mMappingMode == MAPPING_MODE_READ) ? FILE_MAP_READ : FILE_MAP_ALL_ACCESS;
		HANDLE hFileMapping = ::OpenFileMappingW(desiredAccess, FALSE, mPath.c_str());
		if (hFileMapping != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFileMapping);
		}
		_commit(mFile);
		_close(mFile);
	}
}

bool FileMapping::Open(const WideString& path, const MappingMode mappingMode, const Integer64U size)
{
	if (mFile == -1)
	{
		// Setup open flag and permisson mode.
		//
		int openFlag = _O_BINARY;
		int permissionMode = _S_IREAD;

		if (mappingMode == MAPPING_MODE_READ)
		{
			openFlag |= _O_RDONLY;
		}
		else
		{
			assert(mappingMode == MAPPING_MODE_READ_WRITE);

			openFlag |= _O_CREAT|_O_EXCL|_O_RDWR;
			permissionMode |= _S_IWRITE;
		}

		// Open the file.
		// If we're reading the file, test the size of the file.
		// If we're writing the file, resize the file.
		mFile = _wopen(path.c_str(), openFlag, _SH_DENYNO, permissionMode);
		if (mFile != -1)
		{
			if (mappingMode == MAPPING_MODE_READ)
			{
				struct _stat64 fileState;
				if (!_fstat64(mFile, &fileState))
				{
					assert(fileState.st_size);

					mPath = path;

					mMappingMode = mappingMode;
					
					return true;
				}
			}
			else
			{
				HANDLE hFile = reinterpret_cast<HANDLE>(_get_osfhandle(mFile));
				assert(hFile != INVALID_HANDLE_VALUE);

				LARGE_INTEGER fileSize;
				fileSize.QuadPart = size;
				if (::SetFilePointerEx(hFile, fileSize, NULL, FILE_BEGIN))
				{
					if (::SetEndOfFile(hFile))
					{
						HANDLE hFileMapping = ::CreateFileMappingW(hFile, NULL, PAGE_READWRITE, fileSize.HighPart, fileSize.LowPart, path.c_str());
						assert(hFileMapping != INVALID_HANDLE_VALUE);

						if (hFileMapping != INVALID_HANDLE_VALUE)
						{
							mPath = path;

							mMappingMode = mappingMode;

							return true;
						}
					}
				}
			}
		}
	}

	if (mFile != -1)
	{
		_close(mFile);
		_wremove(path.c_str());
		mFile = -1;
	}

	return false;
}

void* FileMapping::MapToSwapFile(const Integer64U offset, const Integer32U size)
{
	assert(size);

	DWORD desiredAccess = (mMappingMode == MAPPING_MODE_READ) ? FILE_MAP_READ : FILE_MAP_ALL_ACCESS;

	HANDLE hFileMapping = ::OpenFileMappingW(desiredAccess, FALSE, mPath.c_str());
	assert(hFileMapping != INVALID_HANDLE_VALUE);
	if (hFileMapping != INVALID_HANDLE_VALUE)
	{
		ULARGE_INTEGER offsetInFile;
		offsetInFile.QuadPart = offset;
		LPVOID address = ::MapViewOfFile(hFileMapping, desiredAccess, offsetInFile.HighPart, offsetInFile.LowPart, size);
		assert(address);
		if (!address)
		{
			exit(::GetLastError());
		}
		return address;
	}
}

void FileMapping::UnMapFromSwapFile(const void* address, const Integer32U length)
{
	UnmapViewOfFile(address);
}

#else




#endif












LEAVE_NAMESPACE_STOKES
