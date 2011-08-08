#include <fcntl.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <Windows.h>

#include <Stokes/Core/File.hpp>

ENTER_NAMESPACE_STOKES

const int File::sInvalidFile = -1;

File::File() :
	mFile(sInvalidFile)
{
}

File::~File()
{
}

#ifdef STOKES_PLATFORM_WINDOWS

bool File::Open(const WideString& path, const AccessMode accessMode)
{
	if (mFile == sInvalidFile)
	{
		// Setup open flag and permisson mode.
		//
		int openFlag = _O_BINARY;
		int permissionMode = _S_IREAD;

		if (accessMode == ACCESS_MODE_READ)
		{
			openFlag |= _O_RDONLY;
		}
		else
		{
			assert(accessMode == ACCESS_MODE_WRITE);

			openFlag |= _O_CREAT|_O_EXCL|_O_RDWR;
			permissionMode |= _S_IWRITE;
		}

		// Open the file.
		mFile = _wopen(path.c_str(), openFlag, _SH_DENYNO, permissionMode);

		if (mFile != sInvalidFile)
		{
			if (accessMode == ACCESS_MODE_READ)
			{
				struct _stat64 fileState;
				if (!_fstat64(mFile, &fileState))
				{
					assert(fileState.st_size);
					if (fileState.st_size > 0)
					{
						mPath = path;

						mAccessMode = accessMode;
					
						return true;
					}
				}
			}else if (accessMode == ACCESS_MODE_WRITE)
			{
				mPath = path;
				mAccessMode = accessMode;
				return true;
			}
		}
	}

	return false;
}

bool File::Resize(const Integer64U size)
{
	assert(size);

	if ((mAccessMode == ACCESS_MODE_WRITE) && (mFile != sInvalidFile))
	{
		HANDLE hFile = reinterpret_cast<HANDLE>(_get_osfhandle(mFile));
		assert(hFile != INVALID_HANDLE_VALUE);

		LARGE_INTEGER fileSize;
		fileSize.QuadPart = size;
		if (::SetFilePointerEx(hFile, fileSize, NULL, FILE_BEGIN))
		{
			if (::SetEndOfFile(hFile))
			{
				return true;
			}
		}
	}

	return false;
}

void File::Close()
{
	if (mFile != sInvalidFile)
	{
		_commit(mFile);
		_close(mFile);
	}
}

Integer32U File::Read(const Integer64U offset, const Integer32U size, void* address)
{
	assert(mFile != sInvalidFile);
	_lseeki64(mFile, offset, SEEK_SET);
	return _read(mFile, address, size);
}

Integer32U File::Write(const Integer64U offset, const Integer32U size, const void* address)
{
	assert(mFile != sInvalidFile);
	_lseeki64(mFile, offset, SEEK_SET);
	Integer32U writtenSize = _write(mFile, address, size);
	_commit(mFile);
	return writtenSize;
}

#endif

LEAVE_NAMESPACE_STOKES
