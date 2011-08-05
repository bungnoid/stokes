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

	void virtual CalculateWorldBound(Bound& bound) const = 0;

	virtual void Fill(const FieldRef& field) = 0;

protected:

	Integer32U mSample;
};

LEAVE_NAMESPACE_STOKES

#endif
