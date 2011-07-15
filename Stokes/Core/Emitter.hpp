#ifndef EMITTER_HPP
#define EMITTER_HPP

#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Emitter
{
public:

	Emitter();
	virtual ~Emitter();

	virtual bool Check(const FieldRef& field) const = 0;
	virtual void Fill(const FieldRef& field) const = 0;
};

LEAVE_NAMESPACE_STOKES

#endif
