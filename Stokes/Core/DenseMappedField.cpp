#include <Stokes/Core/DenseMappedField.hpp>

ENTER_NAMESPACE_STOKES

DenseMappedField::DenseMappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const Integer32U pagedSliceCount) :
	MappedField(localToWorld, bound, dimension, arity, MappedField::STORAGE_MODE_SLICE, pagedSliceCount)
{
}

DenseMappedField::~DenseMappedField()
{
}

Float* DenseMappedField::Access(const Vectoriu& index)
{
	const Integer32U sliceLength = mDimension.x * mDimension.y;
	const Integer64U sliceIndex = sliceLength * index.z;
	Float* sliceAddress = MappedField::Map(sliceIndex, sliceLength);

	const Integer32U elementIndexInSlice = (mDimension.x * index.y + index.x) * mArity;
	return (sliceAddress + elementIndexInSlice);
}

LEAVE_NAMESPACE_STOKES
