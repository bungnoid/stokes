#include <Stokes/Core/SparseMappedField.hpp>

ENTER_NAMESPACE_STOKES

SparseMappedField::SparseMappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const Integer32U pagedBlockCount, const Integer32U blockDimension) :
	MappedField(localToWorld, bound, dimension, arity, MappedField::STORAGE_MODE_BLOCK, pagedBlockCount),
	mBlockDimension(blockDimension)
{
	assert((blockDimension & 1) == 0);

	mDimension.x = (mDimension.x & 1) ? (mDimension.x + 1) / mBlockDimension * mBlockDimension : mDimension.x;
	mDimension.y = (mDimension.y & 1) ? (mDimension.y + 1) / mBlockDimension * mBlockDimension : mDimension.y;
	mDimension.z = (mDimension.z & 1) ? (mDimension.z + 1) / mBlockDimension * mBlockDimension : mDimension.z;
}

SparseMappedField::~SparseMappedField()
{
}

Float* SparseMappedField::Access(const Vectoriu& index)
{
	const Integer32U blockLength = mBlockDimension * mBlockDimension * mBlockDimension;

	const Vectori64u blockIndex(index.x / mBlockDimension, index.y / mBlockDimension, index.z / mBlockDimension);
	const Vectoriu blocksDimension(mDimension.x / mBlockDimension, mDimension.y / mBlockDimension, mDimension.z / mBlockDimension);
	const Integer64U linearBlockIndex = (blocksDimension.x * blocksDimension.y * blockIndex.z + blocksDimension.x * blockIndex.y + blockIndex.x) * blockLength;

	Float* blockAddress = MappedField::Map(linearBlockIndex, blockLength);

	const Vectoriu subBlockIndex(index.x % mBlockDimension, index.y % mBlockDimension, index.z % mBlockDimension);
	const Integer32U linearSubBlockIndex = (mBlockDimension * mBlockDimension * subBlockIndex.z + mBlockDimension * subBlockIndex.y + subBlockIndex.x) * mArity;
	return (blockAddress + linearSubBlockIndex);
}

LEAVE_NAMESPACE_STOKES
