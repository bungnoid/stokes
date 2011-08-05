#include <Stokes/Core/NoisedEmitter.hpp>

ENTER_NAMESPACE_STOKES

NoisedEmitter::NoisedEmitter() :
	mScale(1.0f, 1.0f, 1.0f),

	mOffset(0.0f, 0.0f, 0.0f),

	mH(0.5f),
	mDisplacedH(0.5f),

	mLacunarity(1.0f),
	mDisplacedLacunarity(1.0f),

	mOctave(1.0f),
	mDisplacedOctave(1.0f),

	mAmplitude(1.0f),
	mDisplacedAmplitude(1.0f)
{
}

NoisedEmitter::~NoisedEmitter()
{
}

void NoisedEmitter::SetScale(const Vectorf& scale)
{
	mScale = scale;
}

const Vectorf& NoisedEmitter::GetScale() const
{
	return mScale;
}

void NoisedEmitter::SetOffset(const Vectorf& offset)
{
	mOffset = offset;
}

const Vectorf& NoisedEmitter::GetOffset() const
{
	return mOffset;
}

void NoisedEmitter::SetH(const Float h)
{
	mH = h;
}

Float NoisedEmitter::GetH() const
{
	return mH;
}

void NoisedEmitter::SetDisplacedH(const Float displacedH)
{
	mDisplacedH = displacedH;
}

Float NoisedEmitter::GetDisplacedH() const
{
	return mDisplacedH;
}

void NoisedEmitter::SetLacunarity(const Float lacunarity)
{
	mLacunarity = lacunarity;
}

Float NoisedEmitter::GetLacunarity() const
{
	return mLacunarity;
}

void NoisedEmitter::SetDisplacedLacunarity(const Float displacedLacunarity)
{
	mDisplacedLacunarity = displacedLacunarity;
}

Float NoisedEmitter::GetDisplacedLacunarity() const
{
	return mDisplacedLacunarity;
}

void NoisedEmitter::SetOctave(const Float octave)
{
	mOctave = octave;
}

Float NoisedEmitter::GetOctave() const
{
	return mOctave;
}

void NoisedEmitter::SetDisplacedOctave(const Float displacedOctave)
{
	mDisplacedOctave = displacedOctave;
}

Float NoisedEmitter::GetDisplacedOctave() const
{
	return mDisplacedOctave;
}

void NoisedEmitter::SetAmplitude(const Float amplitude)
{
	mAmplitude = amplitude;
}

Float NoisedEmitter::GetAmplitude() const
{
	return mAmplitude;
}

void NoisedEmitter::SetDisplacedAmplitude(const Float displacedAmplitude)
{
	mDisplacedAmplitude = displacedAmplitude;
}

Float NoisedEmitter::GetDisplacedAmplitude() const
{
	return mDisplacedAmplitude;
}

LEAVE_NAMESPACE_STOKES
