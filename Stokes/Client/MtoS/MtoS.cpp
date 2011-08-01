#include <maya/MFileIO.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MLibrary.h>

#include <Stokes/Maya/MayaNurbsSurfaceEmitter.hpp>

int main(int argc, char* argv[])
{
	MStatus S = MLibrary::initialize(argv[0], true);
	CHECK_MSTATUS(S);

	S = MFileIO::open(argv[1]);
	CHECK_MSTATUS(S);

	Stokes::EmitterRef nurbsSurfaceEmitter;
	for (MItDependencyNodes itr(MFn::kNurbsSurface); !itr.isDone(); itr.next())
	{
		MObject mayaObject(itr.item());
		if (mayaObject.hasFn(MFn::kNurbsSurface))
		{
			nurbsSurfaceEmitter.reset(new Stokes::MayaNurbsSurfaceEmitter(mayaObject));
		}
	}

	MLibrary::cleanup();
	return EXIT_SUCCESS;
}
