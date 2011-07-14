#include <Stokes/Core/Sampler.hpp>

ENTER_NAMESPACE_STOKES

Sampler::Sampler(const FieldRef& field, const AddressingMode addressingMode) :
	mField(field),
	mAddressingMode(addressingMode)
{
}

Sampler::~Sampler()
{
}

LEAVE_NAMESPACE_STOKES
