#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Stokes/Core/MappedArray.hpp>

#include <Windows.h>

ENTER_NAMESPACE_STOKES

MappedArray::MappedArray(const DataType dataType, const MappingMode mappingMode) :
	Array(dataType),
	mMappingMode(mappingMode),
	mMappedFile(-1)
{
}

MappedArray::~MappedArray()
{
	Resize(0);
}

bool MappedArray::OpenMappedFile(const WideString& pathToMappedFile)
{
	if (mMappedFile == -1)
	{
		// Setup open flag and permisson mode.
		//
		int openFlag = _O_BINARY;
		int permissionMode = _S_IREAD;

		if (mMappingMode == MAPPING_MODE_READ_ONLY)
		{
			openFlag |= _O_RDONLY;
		}
		else
		{
			assert(mMappingMode == MAPPING_MODE_READ_WRITE);

			openFlag |= _O_CREAT|_O_EXCL|_O_RDWR;
			permissionMode |= _S_IWRITE;
		}

		// Open the file.
		// If we're reading the file, test the size of the file.
		// If we're writing the file, resize the file.
		mMappedFile = _wopen(pathToMappedFile.c_str(), openFlag, _SH_DENYNO, permissionMode);
		if (mMappedFile != -1)
		{
			if (mMappingMode == MAPPING_MODE_READ_ONLY)
			{
				struct _stat64 fileState;
				if (!_fstat64(mMappedFile, &fileState))
				{
					Integer32U dataTypeSize = GetDataTypeSize(mDataType);
					assert(mLength % dataTypeSize == 0);
					mLength = fileState.st_size / dataTypeSize;

					mPathToMappedFile = pathToMappedFile;
					
					return true;
				}
			}
			else
			{
				mPathToMappedFile = pathToMappedFile;

				return true;
			}
		}
	}

	return false;
}

const WideString& MappedArray::GetPathToMappedFile() const
{
	return mPathToMappedFile;
}

MappedArray::MappingMode MappedArray::GetMappingMode() const
{
	return mMappingMode;
}

Integer64U MappedArray::Resize(const Integer64U length)
{
	assert(mMappedFile != -1);

	if (length == 0)
	{
		if (mMappedFile!= -1)
		{
			HANDLE hFileMapping = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, mPathToMappedFile.c_str());
			if (hFileMapping != INVALID_HANDLE_VALUE)
			{
				if (CloseHandle(hFileMapping) == TRUE)
				{
					_commit(mMappedFile);
					_close(mMappedFile);
					mMappedFile = -1;
				}
			}
		}
		return 0;
	}

	if (mMappingMode == MAPPING_MODE_READ_ONLY)
	{
		return GetSize();
	}
	else
	{
		
		if (mMappedFile != -1)
		{
			HANDLE hMappedFile = reinterpret_cast<HANDLE>(_get_osfhandle(mMappedFile));
			assert(hMappedFile != INVALID_HANDLE_VALUE);

			LARGE_INTEGER fileSize;
			fileSize.QuadPart = GetDataTypeSize(mDataType) * length;

			if (::SetFilePointerEx(hMappedFile, fileSize, NULL, FILE_BEGIN))
			{
				::SetEndOfFile(hMappedFile);

				HANDLE hFileMapping = ::CreateFileMappingW(hMappedFile, NULL, PAGE_READWRITE, fileSize.HighPart, fileSize.LowPart, mPathToMappedFile.c_str());
				assert(hFileMapping != INVALID_HANDLE_VALUE);

				mLength = length;

				return fileSize.QuadPart;
			}
		}
	}

	return 0;
}

void* MappedArray::Access(const Integer64U offset, const Integer32U length)
{
	ULARGE_INTEGER offsetInFile;
	offsetInFile.QuadPart = offset;

	DWORD desiredAccess = (mMappingMode == MAPPING_MODE_READ_ONLY) ? FILE_MAP_READ : FILE_MAP_ALL_ACCESS;

	HANDLE hFileMapping = OpenFileMappingW(desiredAccess, FALSE, mPathToMappedFile.c_str());
	if (hFileMapping != INVALID_HANDLE_VALUE)
	{
		void* address = MapViewOfFile(hFileMapping, desiredAccess, offsetInFile.HighPart, offsetInFile.LowPart, GetDataTypeSize(mDataType) * length);
		assert(address);
		return address;
	}

	return NULL;
}

void MappedArray::Flush(void* address)
{
	UnmapViewOfFile(address);
}

LEAVE_NAMESPACE_STOKES
