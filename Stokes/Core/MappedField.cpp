#include <Stokes/Core/MappedField.hpp>

ENTER_NAMESPACE_STOKES

MappedField::MappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const StorageMode storageMode, const Integer32U pageCount) :
	Field(localToWorld, bound, dimension, arity),
	mFile(new File),
	mStorageMode(storageMode),
	mPageCount(pageCount)
{
}

MappedField::~MappedField()
{
	if (mFile)
	{
		for (std::map<Integer64U, Segement>::iterator itr = mSegements.begin(); itr != mSegements.end(); ++ itr)
		{
			mFile->Write(itr->first, itr->second.size, itr->second.address);
		}
	}
}

const FileRef& MappedField::GetFile() const
{
	return mFile;
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
		// Page out the LRU segement.
		//
		Integer64U leastUsedTime = ULLONG_MAX, mostUsedTime = 0;
		std::map<Integer64U, Segement>::reverse_iterator leastUsedSegementItr;
		for (std::map<Integer64U, Segement>::reverse_iterator itr = mSegements.rbegin(); itr != mSegements.rend(); ++ itr)
		{
			if (itr->second.usedTime <= leastUsedTime)
			{
				leastUsedTime = itr->second.usedTime;
				leastUsedSegementItr = itr;
			}
		}

		void* address = leastUsedSegementItr->second.address;
		Integer32U writtenBytes = mFile->Write(leastUsedSegementItr->first, leastUsedSegementItr->second.size, address);

		// Read data into allocated memory.
		Integer32U readBytes = mFile->Read(linearOffset, neededSize, address);
		assert(readBytes == writtenBytes);
		assert(writtenBytes == leastUsedSegementItr->second.size);

		mSegements.erase(leastUsedSegementItr->first);

		Segement newSegement(neededSize, address);
		mSegements.insert(std::make_pair(linearOffset, newSegement));

		return reinterpret_cast<Float*>(address);
	}

	Segement newSegement(neededSize, malloc(neededSize));
	memset(newSegement.address, 0, neededSize);
	mSegements.insert(std::make_pair(linearOffset, newSegement));
	return (reinterpret_cast<Float*>(newSegement.address));
}

LEAVE_NAMESPACE_STOKES
