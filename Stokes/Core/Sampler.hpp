#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Sampler
{
public:

	enum AddressingMode
	{
		ADDRESSSING_MODE_CLAMP,
		ADDRESSSING_MODE_CLAMP_TO_EDGE,
		ADDRESSSING_MODE_MIRROR,
		ADDRESSSING_MODE_REPEAT,
	};

	Sampler();
	virtual ~Sampler();

	virtual void SampleSlice(const FieldRef& field, const SamplerAddressingMode addressingMode, const WideString& attributeName, const Interger32U sliceIndex) = 0;
	virtual void SampleBlock(const FieldRef& field, const SamplerAddressingMode addressingMode, const WideString& attributeName, const Vectorui& blockIndex) = 0;
	
protected:

	FieldRef mField;
	
};

LEAVE_NAMESPACE_STOKES

#endif
