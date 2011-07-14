#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <Stokes/Core/Field.hpp>
#include <Stokes/Core/FieldCache.hpp>

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

	Sampler(const FieldRef& field, const AddressingMode addressingMode);
	virtual ~Sampler();

	virtual void SampleSlice(const WideString& attributeName, const Integer32U sliceIndex, FieldCache& fieldCache) = 0;
	virtual void SampleBlock(const WideString& attributeName, const Vectoriu& blockIndex, FieldCache& fieldCache) = 0;
	
protected:

	FieldRef mField;
	AddressingMode mAddressingMode;
};

LEAVE_NAMESPACE_STOKES

#endif
