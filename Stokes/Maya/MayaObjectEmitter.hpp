#ifndef MAYAOBJECTEMITTER_HPP
#define MAYAOBJECTEMITTER_HPP

#include <maya/MObject.h>

#include <Stokes/Core/NoisedEmitter.hpp>

#include <Stokes/Maya/API.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_MAYA_API MayaObjectEmitter : public NoisedEmitter
{
public:

	MayaObjectEmitter(const MObject& mayaObject);
	virtual ~MayaObjectEmitter();

	virtual void CalculateWorldBound(Bound& bound) const = 0;

	virtual void Fill(const FieldRef& field) = 0;

protected:

	MObject mMayaObject;
};

LEAVE_NAMESPACE_STOKES

#endif
