#ifndef MAPPEDARRAY_HPP
#define MAPPEDARRAY_HPP

#include <string>

#include <Stokes/Core/LinearArray.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API MappedArray : LinearArray
{
public:

	static Integer32U GetCacheSize();
	static void SetCacheLength(const Integer32U cacheSize);

private:

	static Integer32U sCacheSize;

public:

	MappedArray(const WideString& pathToMappedFile, const DataType dataType, const Integer64U length);
	virtual ~MappedArray();

	const WideString& GetPathToMappedFile() const;

	Integer64U Resize(const DataType dataType, const Integer64U length);

	virtual void PreAccess(const Integer64U index);
	virtual void* Access(const Integer64U index);
	virtual void PostAccess(const Integer64U index);

private:

	WideString mPathToMappedFile;
	int mMappedFile;
};

LEAVE_NAMESPACE_STOKES

#endif
