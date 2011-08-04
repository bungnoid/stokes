#ifndef STOKES_CORE_EMITTER_HPP
#define STOKES_CORE_EMITTER_HPP

#include <set>

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API Emitter
{
public:

	Emitter();
	virtual ~Emitter();

	void SetSample(const Integer32U sample);
	Integer32U GetSample() const;

	void SetNoiseH(const Float noiseH);
	Float GetNoiseH() const;

	void SetNoiseHDisplaced(const Float noiseHDisplaced);
	Float GetNoiseHDisplaced() const;

	void SetNoiseLacunarity(const Float noiseLacunarity);
	Float GetNoiseLacunarity() const;

	void SetNoiseLacunarityDisplaced(const Float noiseLacunarityDisplaced);
	Float GetNoiseLacunarityDisplaced() const;

	void SetNoiseOctave(const Float noiseOctave);
	Float GetNoiseOctave() const;

	void SetNoiseOctaveDisplaced(const Float noiseOctaveDisplaced);
	Float GetNoiseOctaveDisplaced() const;

	void SetNoisePeriod(const Float noiseOctavesPeriod);
	Float GetNoisePeriod() const;

	void SetNoisePeriodDisplaced(const Float noiseAmplitude);
	Float GetNoisePeriodDisplaced() const;

	void SetNoiseAmplitude(const Float noiseAmplitude);
	Float GetNoiseAmplitude() const;

	void SetNoiseAmplitudeDisplaced(const Float noiseAmplitudeDisplaced);
	Float GetNoiseAmplitudeDisplaced() const;

	void virtual CalculateWorldBound(Bound& bound) const = 0;

	virtual void Fill(const FieldRef& field) = 0;

protected:

	Integer32U mSample;

	Float mNoiseH;
	Float mNoiseHDisplaced;

	Float mNoiseLacunarity;
	Float mNoiseLacunarityDisplaced;

	Float mNoiseOctave;
	Float mNoiseOctaveDisplaced;

	Float mNoisePeriod;
	Float mNoisePeriodDisplaced;

	Float mNoiseAmplitude;
	Float mNoiseAmplitudeDisplaced;
};

typedef boost::shared_ptr<Emitter> EmitterRef;

LEAVE_NAMESPACE_STOKES

#endif
