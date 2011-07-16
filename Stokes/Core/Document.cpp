#include <fstream>

#include <rapidxml.hpp>

#include <Stokes/Core/Document.hpp>

ENTER_NAMESPACE_STOKES

Document::Document()
{
}

Document::~Document()
{
}

bool Document::Read(const WideString& fileName)
{
	return false;
}

bool Document::Write(const WideString& fileName)
{
	return false;
}

LEAVE_NAMESPACE_STOKES
