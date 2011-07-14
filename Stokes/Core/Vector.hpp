#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

#include <Stokes/Core/DataType.hpp>

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
	Vector(const Vector& copy)
	{
		x = copy.x;
		y = copy.y;
		z = copy.z;
		w = copy.w;
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
