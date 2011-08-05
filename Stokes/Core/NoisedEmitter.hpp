#ifndef STOKES_CORE_NOISEDEMITTER_HPP
#define STOKES_CORE_NOISEDEMITTER_HPP

#include <Stokes/Core/Emitter.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API NoisedEmitter : public Emitter
{
public:

	NoisedEmitter();
	virtual ~NoisedEmitter();

	void SetScale(const Vectorf& scale);
	const Vectorf& GetScale() const;

	void SetOffset(const Vectorf& offset);
	const Vectorf& GetOffset() const;

	void SetH(const Float noiseH);
	Float GetH() const;

	void SetDisplacedH(const Float displacedH);
	Float GetDisplacedH() const;

	void SetLacunarity(const Float noiseLacunarity);
	Float GetLacunarity() const;

	void SetDisplacedLacunarity(const Float displacedLacunarity);
	Float GetDisplacedLacunarity() const;

	void SetOctave(const Float octave);
	Float GetOctave() const;

	void SetDisplacedOctave(const Float displacedOctave);
	Float GetDisplacedOctave() const;

	void SetPeriod(const Float period);
	Float GetPeriod() const;

	void SetDisplacedPeriod(const Float displacedPeriod);
	Float GetDisplacedPeriod() const;

	void SetAmplitude(const Float amplitude);
	Float GetAmplitude() const;

	void SetDisplacedAmplitude(const Float displacedAmplitude);
	Float GetDisplacedAmplitude() const;

protected:

	Vectorf mScale;

	Vectorf mOffset;

	Float mH;
	Float mDisplacedH;

	Float mLacunarity;
	Float mDisplacedLacunarity;

	Float mOctave;
	Float mDisplacedOctave;

	Float mPeriod;
	Float mDisplacedPeriod;

	Float mAmplitude;
	Float mDisplacedAmplitude;
};

typedef boost::shared_ptr<NoisedEmitter> NoisedEmitterRef;

LEAVE_NAMESPACE_STOKES

#endif
