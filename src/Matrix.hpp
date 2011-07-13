#ifndef STOKES_MATRIX_HPP
#define STOKES_MATRIX_HPP

#include <iterator>

#include <DataType.hpp>
#include <Vector.hpp>

ENTER_NAMESPACE_STOKES

template<typename T>
struct Matrix
{
	Matrix(const T* theData = NULL)
	{
		if (theData)
		{
			std::copy(theData, theData + 16, data);
		}
		else
		{
			std::fill_n(data, 16, 0);
			data[0] = data[5] = data[10] = data[15] = 1;
		}
	}
	Matrix(const Matrix& matrix)
	{
		std::copy(matrix.data, matrix.data + 16, data);
	}

	T data[16];
};

template<typename T>
Matrix<T> Invert(const Matrix<T>& matrix)
{
	T tmp[12];
	T src[16];
	T dst[16];
	T det;

#define TRANSPOSE_ROW(i)	             \
	src[i]		= matrix.data[i * 4];    \
	src[i + 4]	= matrix.data[i * 4 + 1];\
	src[i + 8]	= matrix.data[i * 4 + 2];\
	src[i + 12]	= matrix.data[i * 4 + 3];

	TRANSPOSE_ROW(0);
	TRANSPOSE_ROW(1);
	TRANSPOSE_ROW(2);
	TRANSPOSE_ROW(3);

	tmp[0]	= src[10] * src[15];
	tmp[1]	= src[11] * src[14];
	tmp[2]	= src[9]  * src[15];
	tmp[3]	= src[11] * src[13];
	tmp[4]	= src[9]  * src[14];
	tmp[5]	= src[10] * src[13];
	tmp[6]	= src[8]  * src[15];
	tmp[7]	= src[11] * src[12];
	tmp[8]	= src[8]  * src[14];
	tmp[9]	= src[10] * src[12];
	tmp[10]	= src[8]  * src[13];
	tmp[11]	= src[9]  * src[12];

	dst[0]	 = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4]  * src[7];
	dst[0]	-= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5]  * src[7];
	dst[1]	 = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9]  * src[7];
	dst[1]	-= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8]  * src[7];
	dst[2]	 = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2]	-= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3]	 = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3]	-= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4]	 = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5]  * src[3];
	dst[4]	-= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4]  * src[3];
	dst[5]	 = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8]  * src[3];
	dst[5]	-= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9]  * src[3];
	dst[6]	 = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6]	-= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7]	 = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7]	-= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

	tmp[0]	= src[2] * src[7];
	tmp[1]	= src[3] * src[6];
	tmp[2]	= src[1] * src[7];
	tmp[3]	= src[3] * src[5];
	tmp[4]	= src[1] * src[6];
	tmp[5]	= src[2] * src[5];
	tmp[6]	= src[0] * src[7];
	tmp[7]	= src[3] * src[4];
	tmp[8]	= src[0] * src[6];
	tmp[9]	= src[2] * src[4];
	tmp[10]	= src[0] * src[5];
	tmp[11]	= src[1] * src[4];

	dst[8]	 = tmp[0]  * src[13] + tmp[3]  * src[14] + tmp[4]  * src[15];
	dst[8]	-= tmp[1]  * src[13] + tmp[2]  * src[14] + tmp[5]  * src[15];
	dst[9]	 = tmp[1]  * src[12] + tmp[6]  * src[14] + tmp[9]  * src[15];
	dst[9]	-= tmp[0]  * src[12] + tmp[7]  * src[14] + tmp[8]  * src[15];
	dst[10]	 = tmp[2]  * src[12] + tmp[7]  * src[13] + tmp[10] * src[15];
	dst[10]	-= tmp[3]  * src[12] + tmp[6]  * src[13] + tmp[11] * src[15];
	dst[11]	 = tmp[5]  * src[12] + tmp[8]  * src[13] + tmp[11] * src[14];
	dst[11]	-= tmp[4]  * src[12] + tmp[9]  * src[13] + tmp[10] * src[14];
	dst[12]	 = tmp[2]  * src[10] + tmp[5]  * src[11] + tmp[1]  * src[9];
	dst[12]	-= tmp[4]  * src[11] + tmp[0]  * src[9]  + tmp[3]  * src[10];
	dst[13]	 = tmp[8]  * src[11] + tmp[0]  * src[8]  + tmp[7]  * src[10];
	dst[13]	-= tmp[6]  * src[10] + tmp[9]  * src[11] + tmp[1]  * src[8];
	dst[14]	 = tmp[6]  * src[9]  + tmp[11] * src[11] + tmp[3]  * src[8];
	dst[14]	-= tmp[10] * src[11] + tmp[2]  * src[8]  + tmp[7]  * src[9];
	dst[15]	 = tmp[10] * src[10] + tmp[4]  * src[8]  + tmp[9]  * src[9];
	dst[15]	-= tmp[8]  * src[9]  + tmp[11] * src[10] + tmp[5]  * src[8];

	det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

	det = 1 / det;
	dst[0]  *= det;
	dst[1]  *= det;
	dst[2]  *= det;
	dst[3]  *= det;
	dst[4]  *= det;
	dst[5]  *= det;
	dst[6]  *= det;
	dst[7]  *= det;
	dst[8]  *= det;
	dst[9]  *= det;
	dst[10] *= det;
	dst[11] *= det;
	dst[12] *= det;
	dst[13] *= det;
	dst[14] *= det;
	dst[15] *= det;
	
	return Matrix<T>(dst);
}

template<typename T>
Matrix<T> Transpose(const Matrix<T>& matrix)
{
	Matrix<T> transposed;
	for (Integer32 i = 0; i < 4; ++ i)
	{
		for (Integer32 j = 0; j < 4; ++ j)
		{
			transposed.data[j * 4 + i] = matrix.data[i * 4 + j];
		}
	}
	return transposed;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
	std::copy(matrix.data, matrix.data + 16, std::ostream_iterator<T>(os, " "));
	return os;
}

typedef Matrix<Float>  Matrixf;
typedef Matrix<Double> Matrixd;

LEAVE_NAMESPACE_STOKES

#endif
