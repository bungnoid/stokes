#ifndef LINEAR_SAMPLER_HPP
#define LINEAR_SAMPLER_HPP

#include <Stokes/Core/Sampler.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API LinearSampler : public Sampler
{
public:

	LinearSampler();
	virtual ~LinearSampler();
	
	virtual void SampleSlice(const Field& field, const SamplerAddressingMode addressingMode, const WideString& attributeName, const Interger32U sliceIndex);
	virtual void SampleBlock(const Field& field, const SamplerAddressingMode addressingMode, const WideString& attributeName, const Vectorui& minElementIndex, const Vectorui& maxElementIndex);
};

LEAVE_NAMESPACE_STOKES

#endif
