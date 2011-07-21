#include <Stokes/Core/MappedField.hpp>

ENTER_NAMESPACE_STOKES

MappedField::MappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const StorageMode storageMode, const Integer32U pageCount) :
	Field(localToWorld, bound, dimension, arity),
	mFileMapping(new FileMapping),
	mStorageMode(storageMode),
	mPageCount(pageCount)
{
}

MappedField::~MappedField()
{
	for (std::map<Integer64U, Segement>::iterator itr = mSegements.begin(); itr != mSegements.end(); ++ itr)
	{
		mFileMapping->UnMapFromSwapFile(itr->second.address, );
	}
}

const FileMappingRef& MappedField::GetFileMapping() const
{
	return mFileMapping;
}

MappedField::StorageMode MappedField::GetStorageMode() const
{
	return mStorageMode;
}

Float* MappedField::Map(const Integer64U linearIndex, const Integer32U length)
{
	assert(length);

	const Integer64U linearOffset = linearIndex * mArity * sizeof(Float);
	const Integer32U neededSize = length * mArity * sizeof(Float);

	std::map<Integer64U, Segement>::iterator itr = mSegements.find(linearOffset);
	if (itr != mSegements.end())
	{
		itr->second.usedTime += 1;
		return (reinterpret_cast<Float*>(itr->second.address));
	}
	else if (mSegements.size() >= mPageCount)
	{
		Integer64U leastUsedTime = ULLONG_MAX;
		std::map<Integer64U, Segement>::reverse_iterator leastUsedSegementItr;
		for (std::map<Integer64U, Segement>::reverse_iterator rItr = mSegements.rbegin(); rItr != mSegements.rend(); ++ rItr)
		{
			if (rItr->second.usedTime < leastUsedTime)
			{
				leastUsedSegementItr = rItr;
				leastUsedTime = rItr->second.usedTime;
			}
		}
		mFileMapping->UnMapFromSwapFile(leastUsedSegementItr->second.address, leastUsedSegementItr->second.size);

		mSegements.erase(leastUsedSegementItr->first);
	}

	Segement newSegement(neededSize, mFileMapping->MapToSwapFile(linearOffset, neededSize));
	mSegements.insert(std::make_pair(linearOffset, newSegement));
	return (reinterpret_cast<Float*>(newSegement.address));
}

LEAVE_NAMESPACE_STOKES
