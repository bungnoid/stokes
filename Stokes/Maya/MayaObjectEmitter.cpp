#include <Stokes/Maya/MayaObjectEmitter.hpp>

ENTER_NAMESPACE_STOKES

MayaObjectEmitter::MayaObjectEmitter(const MObject& mayaObject) :
	mMayaObject(mayaObject)
{
}

MayaObjectEmitter::~MayaObjectEmitter()
{
}
	
LEAVE_NAMESPACE_STOKES