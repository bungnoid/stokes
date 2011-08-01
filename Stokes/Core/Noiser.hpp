#ifndef STOKES_CORE_NOISER_HPP
#define STOKES_CORE_NOISER_HPP

#include <Stokes/Core/DataType.hpp>
#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_CORE_API Noiser
{
public:

	static Float Noise(Float x, Float y, Float z);

	static Float FractalBrownianMotion(Vectorf localPoint, Float H, Float octave, Float gain, Float lacunarity);

	static Float Turbulence(Vectorf localPoint, Float frequency);
};

LEAVE_NAMESPACE_STOKES

#endif
