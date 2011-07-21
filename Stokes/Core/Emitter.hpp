#ifndef EMITTER_HPP
#define EMITTER_HPP

#include <set>

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Emitter
{
public:

	Emitter();
	virtual ~Emitter();

	void SetNoiseOctaves(const Float noiseOctaves);
	Float GetNoiseOctaves() const;
	void SetNoiseOctavesDisplaced(const Float noiseOctavesDisplaced);
	Float GetNoiseOctavesDisplaced() const;
	void SetNoisePeriod(const Float noiseOctavesPeriod);
	Float GetNoisePeriod() const;
	void SetNoisePeriodDisplaced(const Float noiseAmplitude);
	Float GetNoisePeriodDisplaced() const;
	void SetNoiseAmplitudeDisplaced(const Float noiseAmplitudeDisplaced);
	Float GetNoiseAmplitudeDisplaced() const;

	virtual Bound CalculateWorldBound() const = 0;

	virtual void Fill(const FieldRef& field) = 0;

protected:

	Float mNoiseOctaves;
	Float mNoiseOctavesDisplaced;
	Float mNoisePeriod;
	Float mNoisePeriodDisplaced;
	Float mNoiseAmplitude;
	Float mNoiseAmplitudeDisplaced;
};

typedef boost::shared_ptr<Emitter> EmitterRef;

LEAVE_NAMESPACE_STOKES

#endif
