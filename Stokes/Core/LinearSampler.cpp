#include <Stokes/Core/LinearSampler.hpp>

ENTER_NAMESPACE_STOKES

LinearSampler::LinearSampler(const FieldRef& field, const AddressingMode addressingMode) :
	Sampler(field, addressingMode)
{
}

LinearSampler::~LinearSampler()
{
}

void LinearSampler::SampleSlice(const FieldRef& field, const Sampler::AddressingMode addressingMode, const WideString& attributeName, const Integer32U sliceIndex)
{
}


void LinearSampler::SampleBlock(const FieldRef& field, const Sampler::AddressingMode addressingMode, const WideString& attributeName, const Vectoriu& minElementIndex, const Vectoriu& maxElementIndex)
{
}
	
LEAVE_NAMESPACE_STOKES
