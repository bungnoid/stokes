#include <Stokes/Core/Emitter.hpp>
#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

Emitter::Emitter()
{
}

Emitter::~Emitter()
{
}

void Emitter::SetNoiseOctaves(const Float noiseOctaves)
{
	mNoiseOctaves = noiseOctaves;
}

Float Emitter::GetNoiseOctaves() const
{
	return mNoiseOctaves;
}

void Emitter::SetNoiseOctavesDisplaced(const Float noiseOctavesDisplaced)
{
	mNoiseOctavesDisplaced = noiseOctavesDisplaced;
}

Float Emitter::GetNoiseOctavesDisplaced() const
{
	return mNoiseOctavesDisplaced;
}

void Emitter::SetNoisePeriod(const Float noisePeriod)
{
	mNoisePeriod = noisePeriod;
}

Float Emitter::GetNoisePeriod() const
{
	return mNoisePeriod;
}

void Emitter::SetNoisePeriodDisplaced(const Float noisePeriodDisplaced)
{
	mNoisePeriodDisplaced = noisePeriodDisplaced;
}

Float Emitter::GetNoisePeriodDisplaced() const
{
	return mNoisePeriodDisplaced;
}

void Emitter::SetNoiseAmplitudeDisplaced(const Float noiseAmplitudeDisplaced)
{
	mNoiseAmplitudeDisplaced = noiseAmplitudeDisplaced;
}

Float Emitter::GetNoiseAmplitudeDisplaced() const
{
	return mNoiseAmplitudeDisplaced;
}

LEAVE_NAMESPACE_STOKES
