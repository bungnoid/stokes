#ifndef STOKES_VECTOR_HPP
#define STOKES_VECTOR_HPP

#include <iostream>

#include <DataType.hpp>

ENTER_NAMESPACE_STOKES

template<typename T>
struct Vector
{
	Vector(const T theX = 0, const T theY = 0, const T theZ = 0, const T theW = 1) :
		x(theX),
		y(theY),
		z(theZ),
		w(theW)
	{
	}

	union
	{
		struct
		{
			T x;
			T y;
			T z;
			T w;
		};
		T xyzw[4];
	};

	friend std::ostream& operator<<(std::ostream& os, const Vector& vector)
	{
		os << vector.x << ' ' << vector.y << ' ' << vector.z << ' ' << vector.w;
		return os;
	}
};

typedef Vector<Float>      Vectorf;
typedef Vector<Integer32>  Vectori;
typedef Vector<Integer32U> Vectoriu;

LEAVE_NAMESPACE_STOKES

#endif
