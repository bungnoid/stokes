#ifndef STOKES_MAPPEDARRAY_HPP
#define STOKES_MAPPEDARRAY_HPP

#include <string>

#include <LinearArray.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API MappedArray : LinearArray
{
public:

	static Integer32U GetCacheSize();
	static void SetCacheLength(const Integer32U cacheSize);

private:

	static Integer32U sCacheSize;

public:

	MappedArray(const std::wstring& pathToMappedFile, const DataType dataType, const Integer64U length);
	virtual ~MappedArray();

	const std::wstring& GetPathToMappedFile() const;

	Integer64U Resize(const DataType dataType, const Integer64U length);

	virtual void PreAccess(const Integer64U index);
	virtual void* Access(const Integer64U index);
	virtual void PostAccess(const Integer64U index);

private:

	std::wstring mPathToMappedFile;
	int mMappedFile;
};

LEAVE_NAMESPACE_STOKES

#endif
