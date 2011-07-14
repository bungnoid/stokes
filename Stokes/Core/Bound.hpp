#ifndef BOUND_HPP
#define BOUND_HPP

#include <cfloat>

#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

struct Bound
{
	Bound() :
		min(  FLT_MAX,   FLT_MAX,   FLT_MAX),
		max(- FLT_MAX, - FLT_MAX, - FLT_MAX)
	{
	}

	void Extend(const Vectorf& position)
	{
		min.x = std::min(min.x, position.x);
		min.y = std::min(min.y, position.y);
		min.z = std::min(min.z, position.z);

		max.x = std::min(max.x, position.x);
		max.y = std::min(max.y, position.y);
		max.z = std::min(max.z, position.z);
	}

	Vectorf min;
	Vectorf max;
};


LEAVE_NAMESPACE_STOKES

#endif
