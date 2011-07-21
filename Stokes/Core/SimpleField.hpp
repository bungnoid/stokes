#ifndef SIMPLEFIELD_HPP
#define SIMPLEFIELD_HPP

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API SimpleField : public Field
{
public:

	SimpleField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity);
	~SimpleField();

	Float* Access(const Vectoriu& index);

private:

	void* mAddress;
};

typedef boost::shared_ptr<SimpleField> SimpleFieldRef;

LEAVE_NAMESPACE_STOKES

#endif
