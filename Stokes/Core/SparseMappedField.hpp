#ifndef SPARSEFIELD_HPP
#define SPARSEFIELD_HPP

#include <Stokes/Core/MappedField.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API SparseMappedField : public MappedField
{
public:

	SparseMappedField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity, const Integer32U pagedBlockCount, const Integer32U blockDimension);
	~SparseMappedField();

	Integer32U GetBlockDimension() const;

	Float* Access(const Vectoriu& index);

private:

	Integer32U mBlockDimension;
};

typedef boost::shared_ptr<SparseMappedField> SparseMappedFieldRef;

LEAVE_NAMESPACE_STOKES

#endif
