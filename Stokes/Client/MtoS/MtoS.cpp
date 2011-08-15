#include <maya/MFileIO.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MLibrary.h>

#include <Stokes/Core/DenseMappedField.hpp>
#include <Stokes/Core/SimpleField.hpp>

#include <Stokes/Maya/NurbsCurveEmitter.hpp>
#include <Stokes/Maya/NurbsSurfaceEmitter.hpp>

int main(int argc, char* argv[])
{
	MStatus S = MLibrary::initialize(argv[0], true);
	CHECK_MSTATUS(S);

	S = MFileIO::open(argv[1]);
	CHECK_MSTATUS(S);

	Stokes::Bound totalBound;

	Stokes::NoisedEmitterRef nurbsCurveEmitter;
	for (MItDependencyNodes itr(MFn::kNurbsCurve); !itr.isDone(); itr.next())
	{
		MObject object(itr.item());
		if (object.hasFn(MFn::kNurbsCurve))
		{
			nurbsCurveEmitter.reset(new Stokes::Maya::NurbsCurveEmitter(object));

			nurbsCurveEmitter->SetSample(10000000);
			nurbsCurveEmitter->SetAmplitude(0.5f);
			nurbsCurveEmitter->SetDisplacedAmplitude(1.0f);
			nurbsCurveEmitter->SetH(0.825f);
			nurbsCurveEmitter->SetDisplacedH(1.525f);
			nurbsCurveEmitter->SetLacunarity(1.15f);
			nurbsCurveEmitter->SetDisplacedLacunarity(5.725f);
			nurbsCurveEmitter->SetOctave(4.5f);
			nurbsCurveEmitter->SetDisplacedOctave(5.5f);


			Stokes::Bound bound;
			nurbsCurveEmitter->CalculateWorldBound(bound);
			totalBound.Extend(bound);

			Stokes::Vectorf scale(2.5f, 2.5f, 2.5f);
			nurbsCurveEmitter->SetScale(scale);

			Stokes::Vectorf offset(- scale.x * 0.5f, - scale.y * 0.5f, - scale.z * 0.5f);
			nurbsCurveEmitter->SetOffset(offset);
		}
	}

	Stokes::NoisedEmitterRef nurbsSurfaceEmitter;
	for (MItDependencyNodes itr(MFn::kNurbsSurface); !itr.isDone(); itr.next())
	{
		MObject object(itr.item());
		if (object.hasFn(MFn::kNurbsSurface))
		{
			nurbsSurfaceEmitter.reset(new Stokes::Maya::NurbsSurfaceEmitter(object));

			nurbsSurfaceEmitter->SetSample(10000);
			nurbsSurfaceEmitter->SetAmplitude(1.15f);
			nurbsSurfaceEmitter->SetDisplacedAmplitude(1.25f);
			nurbsSurfaceEmitter->SetH(0.825f);
			nurbsSurfaceEmitter->SetDisplacedH(0.525f);
			nurbsSurfaceEmitter->SetLacunarity(1.15f);
			nurbsSurfaceEmitter->SetDisplacedLacunarity(5.725f);
			nurbsSurfaceEmitter->SetOctave(1.5f);
			nurbsSurfaceEmitter->SetDisplacedOctave(3.5f);


			Stokes::Bound bound;
			nurbsSurfaceEmitter->CalculateWorldBound(bound);
			totalBound.Extend(bound);

			Stokes::Vectorf scale = bound.Size();
			scale.x *= 0.15f;
			scale.y *= 0.15f;
			scale.z *= 0.15f;
			nurbsSurfaceEmitter->SetScale(scale);

			Stokes::Vectorf offset(- scale.x * 0.5f, - scale.y * 0.5f, - scale.z * 0.5f);
			nurbsSurfaceEmitter->SetOffset(offset);
		}
	}

	Stokes::Matrixf identity;	

	Stokes::Vectoriu dimension(512, 512, 512);

	Stokes::Integer32U arity = 1;

	//Stokes::DenseMappedFieldRef field(new Stokes::DenseMappedField(identity, bound, dimension, arity, 256));
	//Stokes::FileRef fieldFile = field->GetFile();
	//if (fieldFile->Open(L"MtoS.raw", Stokes::File::ACCESS_MODE_WRITE))
	//{
	//	if (fieldFile->Resize(field->GetSize()))
	//	{
	//		nurbsSurfaceEmitter->Fill(field);
	//	}
	//}

	Stokes::SimpleFieldRef field(new Stokes::SimpleField(identity, totalBound, dimension, arity));
	nurbsCurveEmitter->Fill(field);
	nurbsSurfaceEmitter->Fill(field);
	field->Save(L"E:/MtoS.raw", false);
	
	MLibrary::cleanup();
	return EXIT_SUCCESS;
}
