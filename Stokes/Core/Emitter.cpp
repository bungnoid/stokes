#include <Stokes/Core/Emitter.hpp>
#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

Emitter::Emitter() :
	mSample(0),

	mNoiseH(0.5f),
	mNoiseHDisplaced(0.5f),

	mNoiseLacunarity(1.0f),
	mNoiseLacunarityDisplaced(1.0f),

	mNoiseOctave(1.0f),
	mNoiseOctaveDisplaced(1.0f),

	mNoisePeriod(1.0f),
	mNoisePeriodDisplaced(1.0f),

	mNoiseAmplitude(1.0f),
	mNoiseAmplitudeDisplaced(1.0f)
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

void Emitter::SetNoiseH(const Float noiseH)
{
	mNoiseH = noiseH;
}

Float Emitter::GetNoiseH() const
{
	return mNoiseH;
}

void Emitter::SetNoiseHDisplaced(const Float noiseHDisplaced)
{
	mNoiseHDisplaced = noiseHDisplaced;
}

Float Emitter::GetNoiseHDisplaced() const
{
	return mNoiseHDisplaced;
}

void Emitter::SetNoiseLacunarity(const Float noiseLacunarity)
{
	mNoiseLacunarity = noiseLacunarity;
}

Float Emitter::GetNoiseLacunarity() const
{
	return mNoiseLacunarity;
}

void Emitter::SetNoiseLacunarityDisplaced(const Float noiseLacunarityDisplaced)
{
	mNoiseLacunarityDisplaced = noiseLacunarityDisplaced;
}

Float Emitter::GetNoiseLacunarityDisplaced() const
{
	return mNoiseLacunarityDisplaced;
}

void Emitter::SetNoiseOctave(const Float noiseOctave)
{
	mNoiseOctave = noiseOctave;
}

Float Emitter::GetNoiseOctave() const
{
	return mNoiseOctave;
}

void Emitter::SetNoiseOctaveDisplaced(const Float noiseOctaveDisplaced)
{
	mNoiseOctaveDisplaced = noiseOctaveDisplaced;
}

Float Emitter::GetNoiseOctaveDisplaced() const
{
	return mNoiseOctaveDisplaced;
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

void Emitter::SetNoiseAmplitude(const Float noiseAmplitude)
{
	mNoiseAmplitude = noiseAmplitude;
}

Float Emitter::GetNoiseAmplitude() const
{
	return mNoiseAmplitude;
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
