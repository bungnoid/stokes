#ifndef STOKES_FIELD_HPP
#define STOKES_FIELD_HPP

#include <string>

#include <API.hpp>
#include <Array.hpp>
#include <Matrix.hpp>
#include <Vector.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Field
{
public:

	Field(const std::wstring& name, const Vectoriu& totalDim, const Vectoriu& blockDim);
	virtual ~Field();

private:

	std::wstring mName;

	Vectoriu mTotalDim;
	Vectoriu mBlockDim;
};

LEAVE_NAMESPACE_STOKES

#endif
