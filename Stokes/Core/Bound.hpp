#ifndef BOUND_HPP
#define BOUND_HPP

#include <cassert>
#include <cfloat>

#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

struct Bound
{
	Bound(
		const Float minX =   FLT_MAX, const Float minY =   FLT_MAX, const Float minZ =   FLT_MAX,
		const Float maxX = - FLT_MAX, const Float maxY = - FLT_MAX, const Float maxZ = - FLT_MAX
		) :
		min(minX, minY, minZ),
		max(maxX, maxY, maxZ)
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

	Vectorf Size() const
	{
		assert(min.x < max.x);
		assert(min.y < max.y);
		assert(min.z < max.z);

		return Vectorf(max.x - min.x, max.y - min.y, max.z - min.z);
	}

	Vectorf min;
	Vectorf max;
};


LEAVE_NAMESPACE_STOKES

#endif
