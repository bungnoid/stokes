#include <Stokes/Core/Emitter.hpp>
#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

Emitter::Emitter() :
	mSample(0)
{
}

Emitter::~Emitter()
{
}

void Emitter::SetSample(const Integer32U sample)
{
	mSample = sample;
}

Integer32U Emitter::GetSample() const
{
	return mSample;
}

LEAVE_NAMESPACE_STOKES
