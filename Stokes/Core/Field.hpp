#ifndef STOKES_CORE_FIELD_HPP
#define STOKES_CORE_FIELD_HPP

#include <Stokes/Core/Bound.hpp>
#include <Stokes/Core/Matrix.hpp>
#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API Field
{
public:

	Field(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity);
	virtual ~Field();

	const Matrixf& GetLocalToWorld() const;
	const Matrixf& GetWorldToLocal() const;

	const Bound& GetBound() const;

	const Vectoriu& GetDimension() const;

	Integer32U GetArity() const;

	Integer64U GetSize() const;

	Vectorf CalculateLocalPointFromIndex(const Vectoriu& index) const;
	Vectorf CalculateWorldPointFromIndex(const Vectoriu& index) const;
	Bool CalculateIndexFromWorldPoint(const Vectorf& worldPoint, Vectoriu& rIndex) const;

	virtual Float* Access(const Vectoriu& index) = 0;

protected:

	Matrixf        mLocalToWorld;
	Matrixf        mWorldToLocal;

	Bound          mBound;
	
	Vectoriu       mDimension;

	Integer32U     mArity;
};

typedef boost::shared_ptr<Field> FieldRef;

LEAVE_NAMESPACE_STOKES

#endif
