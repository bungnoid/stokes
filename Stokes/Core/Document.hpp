#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

/**
 * Serialize the all entities to external document.
 *
 * Document
 * -# Cameras
 *	-# Camera
 * -# Fields
 *	-# Type
 *	-# Alias
 *	-# Array
 */
class STOKES_API Document
{
public:

	Document();
	~Document();

	bool Read(const WideString& fileName);
	bool Write(const WideString& fileName); 

	void Serialize(const FieldRef& field);
};

LEAVE_NAMESPACE_STOKES

#endif
