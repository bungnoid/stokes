#include <cmath>

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

Field::Field(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& totalDimension, const Integer32U arity) :
	mLocalToWorld(localToWorld),
	mBound(bound),
	mDimension(totalDimension),
	mArity(arity)
{
}

Field::~Field()
{
}

const Matrixf& Field::GetLocalToWorld() const
{
	return mLocalToWorld;
}

const Matrixf& Field::GetWorldToLocal() const
{
	return mWorldToLocal;
}
	
const Bound& Field::GetBound() const
{
	return mBound;
}

const Vectoriu& Field::GetDimension() const
{
	return mDimension;
}

Integer32U Field::GetArity() const
{
	return mArity;
}

Integer64U Field::GetSize() const
{
	return mDimension.x * mDimension.y * mDimension.z * mArity * sizeof(Float);
}

Vectorf Field::CalculateLocalPointFromIndex(const Vectoriu& index) const
{
	const Vectorf totalSize(mBound.Size());
	const Vectorf elementSize(totalSize.x / mDimension.x, totalSize.y / mDimension.y, totalSize.z / mDimension.z);
	const Vectorf localPoint(elementSize.x * (index.x + 0.5f), elementSize.y * (index.y + 0.5f), elementSize.z * (index.z + 0.5f));

	return Transform(mLocalToWorld, localPoint);
}

Bool Field::CalculateIndexFromWorldPoint(const Vectorf& worldPoint, Vectoriu& rIndex) const
{
	Vectorf localPoint(Transform(mWorldToLocal, worldPoint));
	if (mBound.IsContained(localPoint))
	{
		localPoint -= mBound.min;

		const Vectorf totalSize(mBound.Size());
		const Vectorf elementSize(totalSize.x / mDimension.x, totalSize.y / mDimension.y, totalSize.z / mDimension.z);

		rIndex.x = static_cast<int>(floor(localPoint.x / elementSize.x));
		rIndex.y = static_cast<int>(floor(localPoint.y / elementSize.y));
		rIndex.z = static_cast<int>(floor(localPoint.z / elementSize.z));

		return true;
	}

	return false;
}

LEAVE_NAMESPACE_STOKES
