#ifndef STOKES_MAYA_NURBSCURVEEMITTER_HPP
#define STOKES_MAYA_NURBSCURVEEMITTER_HPP

#include <Stokes/Maya/ObjectEmitter.hpp>

ENTER_NAMESPACE_STOKES_MAYA

class STOKES_MAYA_API NurbsCurveEmitter : public ObjectEmitter
{
public:

	NurbsCurveEmitter(const MObject& object);
	~NurbsCurveEmitter();

	virtual void CalculateWorldBound(Bound& bound) const;

	virtual void Fill(const FieldRef& field);
};

LEAVE_NAMESPACE_STOKES_MAYA

#endif
