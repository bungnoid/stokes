#ifndef STOKES_MAYA_NURBSSURFACEEMITTER_HPP
#define STOKES_MAYA_NURBSSURFACEEMITTER_HPP

#include <Stokes/Maya/ObjectEmitter.hpp>

ENTER_NAMESPACE_STOKES_MAYA

class STOKES_MAYA_API NurbsSurfaceEmitter : public ObjectEmitter
{
public:

	NurbsSurfaceEmitter(const MObject& mayaObject);
	~NurbsSurfaceEmitter();

	virtual void CalculateWorldBound(Bound& bound) const;

	virtual void Fill(const FieldRef& field);
};

LEAVE_NAMESPACE_STOKES_MAYA

#endif
