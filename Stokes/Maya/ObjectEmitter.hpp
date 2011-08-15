#ifndef STOKES_MAYA_OBJECTEMITTER_HPP
#define STOKES_MAYA_OBJECTEMITTER_HPP

#include <maya/MObject.h>

#include <Stokes/Core/NoisedEmitter.hpp>

#include <Stokes/Maya/API.hpp>

ENTER_NAMESPACE_STOKES_MAYA

class STOKES_MAYA_API ObjectEmitter : public NoisedEmitter
{
public:

	ObjectEmitter(const MObject& mayaObject);
	virtual ~ObjectEmitter();

	virtual void CalculateWorldBound(Bound& bound) const = 0;

	virtual void Fill(const FieldRef& field) = 0;

protected:

	MObject mObject;
};

LEAVE_NAMESPACE_STOKES_MAYA

#endif
