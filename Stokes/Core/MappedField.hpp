#ifndef STOKES_CORE_MAPPEDFIELD_HPP
#define STOKES_CORE_MAPPEDFIELD_HPP

#include <map>

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API MappedField : public Field
{
public:

	enum StorageMode
	{
		STORAGE_MODE_BLOCK,
		STORAGE_MODE_SLICE,
	};
	
public:

	MappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const StorageMode storageMode, const Integer32U pageCount);
	virtual ~MappedField();

	const FileMappingRef& GetFileMapping() const;

	StorageMode GetStorageMode() const;

	Float* Map(const Integer64U linearIndex, const Integer32U length);

protected:

	struct Segement
	{
		Segement(const Integer32U theSize = 0, const void* theAddress = NULL) :
			size(theSize),
			address(const_cast<void*>(theAddress))
		{
			assert(address);
		}
		Integer32U size;
		Integer64U usedTime;
		void*      address;
	};

protected:

	StorageMode                    mStorageMode;
	Integer32U                     mPageCount;
	FileMappingRef                 mFileMapping;
	std::map<Integer64U, Segement> mSegements;
};

LEAVE_NAMESPACE_STOKES

#endif
