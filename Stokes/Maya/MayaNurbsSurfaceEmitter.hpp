#ifndef MAYANURBSSURFACEEMITTER_HPP
#define MAYANURBSSURFACEEMITTER_HPP

#include <maya/MObject.h>

#include <Stokes/Maya/MayaObjectEmitter.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_MAYA_API MayaNurbsSurfaceEmitter : public MayaObjectEmitter
{
public:

	MayaNurbsSurfaceEmitter(const MObject& mayaObject);
	~MayaNurbsSurfaceEmitter();

	virtual void CalculateWorldBound(Bound& bound) const;

	virtual void Fill(const FieldRef& field);
};

LEAVE_NAMESPACE_STOKES

#endif
