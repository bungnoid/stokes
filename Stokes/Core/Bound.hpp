#ifndef STOKES_CORE_BOUND_HPP
#define STOKES_CORE_BOUND_HPP

#include <cassert>
#include <cfloat>

#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

struct Bound
{
	Bound
	(const Float minX =   FLT_MAX, const Float minY =   FLT_MAX, const Float minZ =   FLT_MAX,
	 const Float maxX = - FLT_MAX, const Float maxY = - FLT_MAX, const Float maxZ = - FLT_MAX) :
		min(minX, minY, minZ),
		max(maxX, maxY, maxZ)
	{
	}
	Bound(const Bound& copy) :
		min(copy.min),
		max(copy.max)
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
	bool IsContained(const Vectorf& position) const
	{
		if ((position.x > min.x) && (position.x < max.x))
		{
			if ((position.y > min.y) && (position.y < max.y))
			{
				if ((position.z > min.z) && (position.z < max.z))
				{
					return true;
				}
			}
		}
		return false;
	}

	Vectorf min;
	Vectorf max;
};

LEAVE_NAMESPACE_STOKES

#endif
