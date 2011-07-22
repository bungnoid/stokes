#include <Stokes/Core/SimpleField.hpp>

ENTER_NAMESPACE_STOKES

SimpleField::SimpleField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity) :
	Field(localToWorld, bound, dimension, arity)
{
	mAddress = malloc(dimension.x * dimension.y * dimension.z * arity * sizeof(Float));
	assert(mAddress);
}

SimpleField::~SimpleField()
{
}

Float* SimpleField::Access(const Vectoriu& index)
{
	const Integer32U linearIndex = (mDimension.x * mDimension.y * index.z + mDimension.x * index.y + index.x) * mArity;
	return (reinterpret_cast<Float*>(mAddress) + linearIndex);
}

LEAVE_NAMESPACE_STOKES
