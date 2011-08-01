#include <maya/MFileIO.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MLibrary.h>

#include <Stokes/Core/SimpleField.hpp>

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

	Stokes::Matrixf identity;

	Stokes::Bound bound;
	nurbsSurfaceEmitter->CalculateWorldBound(bound);

	Stokes::Vectoriu dimension(512, 512, 512);

	Stokes::Integer32U arity = 1;

	Stokes::SimpleFieldRef field(new Stokes::SimpleField(identity, bound, dimension, arity));

	nurbsSurfaceEmitter->Fill(field);

	FILE* fp = fopen(argv[2], "wb");
	assert(fp);
	fwrite(field->Access(Stokes::Vectoriu(0, 0, 0)), field->GetSize(), 1, fp);
	fclose(fp);

	MLibrary::cleanup();
	return EXIT_SUCCESS;
}
