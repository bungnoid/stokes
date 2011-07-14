#ifndef LINEAR_SAMPLER_HPP
#define LINEAR_SAMPLER_HPP

#include <Stokes/Core/Sampler.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API LinearSampler : public Sampler
{
public:

	LinearSampler(const FieldRef& field, const AddressingMode addressingMode);
	virtual ~LinearSampler();
	
	virtual void SampleSlice(const FieldRef& field, const Sampler::AddressingMode addressingMode, const WideString& attributeName, const Integer32U sliceIndex);
	virtual void SampleBlock(const FieldRef& field, const Sampler::AddressingMode addressingMode, const WideString& attributeName, const Vectoriu& minElementIndex, const Vectoriu& maxElementIndex);
};

LEAVE_NAMESPACE_STOKES

#endif
