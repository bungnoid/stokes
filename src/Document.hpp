#ifndef STOKES_DOCUMENT_HPP
#define STOKES_DOCUMENT_HPP

#include <string>

#include <API.hpp>

ENTER_NAMESPACE_STOKES

class Field;

class STOKES_API Document
{
public:

	Document(const std::wstring& fileName);
	~Document();

	void Serialize(const Field& field);
};

LEAVE_NAMESPACE_STOKES

#endif
