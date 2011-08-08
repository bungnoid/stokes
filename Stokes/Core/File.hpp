#ifndef STOKES_CORE_FILE_HPP
#define STOKES_CORE_FILE_HPP

#include <Stokes/Core/DataType.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API File
{
public:

	enum AccessMode
	{
		ACCESS_MODE_READ,
		ACCESS_MODE_WRITE
	};

	File();
	~File();

	bool Open(const WideString& path, const AccessMode accessMode);
	bool Resize(const Integer64U size);
	void Close();

	Integer32U Read(const Integer64U offset, const Integer32U size, void* address);
	Integer32U Write(const Integer64U offset, const Integer32U size, const void* address);

private:

	static const int sInvalidFile;

private:

	WideString mPath;

	AccessMode mAccessMode;

	int        mFile;
};

typedef boost::shared_ptr<File> FileRef;

LEAVE_NAMESPACE_STOKES

#endif
