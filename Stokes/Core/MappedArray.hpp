#ifndef MAPPEDARRAY_HPP
#define MAPPEDARRAY_HPP

#include <string>

#include <Stokes/Core/LinearArray.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API MappedArray : public LinearArray
{
public:

	MappedArray(const WideString& pathToMappedFile, const DataType dataType, const Integer64U length);
	virtual ~MappedArray();

	const WideString& GetPathToMappedFile() const;

	Integer64U Resize(const DataType dataType, const Integer64U length);

	virtual void PreAccess(const Integer64U offset, const Integer32U length = 0);
	virtual void* Access(const Integer64U offset, const Integer32U length = 0);
	virtual void PostAccess(const Integer64U offset, const Integer32U length = 0);

private:

	int mMappedFile;

	WideString mPathToMappedFile;
};

LEAVE_NAMESPACE_STOKES

#endif
