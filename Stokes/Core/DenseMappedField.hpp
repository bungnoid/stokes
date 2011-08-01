#ifndef STOKES_CORE_DENSEMAPPEDFIELD_HPP
#define STOKES_CORE_DENSEMAPPEDFIELD_HPP

#include <Stokes/Core/MappedField.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API DenseMappedField : public MappedField
{
public:

	DenseMappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const Integer32U pagedSliceCount);
	~DenseMappedField();

	Integer32U GetPagedSliceCount() const;

	Float* Access(const Vectoriu& index);
};

typedef boost::shared_ptr<DenseMappedField> DenseMappedFieldRef;

LEAVE_NAMESPACE_STOKES

#endif
