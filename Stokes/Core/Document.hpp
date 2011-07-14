#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <Stokes/Core/DataType.hpp>

ENTER_NAMESPACE_STOKES

class Field;

class STOKES_API Document
{
public:

	Document(const WideString& fileName);
	~Document();

	void Serialize(const Field& field);
};

LEAVE_NAMESPACE_STOKES

#endif
