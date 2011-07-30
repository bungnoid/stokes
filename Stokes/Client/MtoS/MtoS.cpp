#include <omp.h>

#include <maya/MBoundingBox.h>
#include <maya/MFileIO.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MLibrary.h>
#include <maya/MMatrix.h>

#include <Stokes/Core/Noiser.hpp>
#include <Stokes/Core/SimpleField.hpp>

int main(int argc, char* argv[])
{
	MStatus S = MLibrary::initialize(argv[0], true);
	CHECK_MSTATUS(S);

	S = MFileIO::open(argv[1]);
	CHECK_MSTATUS(S);

	MFnNurbsSurface surface;
	for (MItDependencyNodes itr(MFn::kNurbsSurface); !itr.isDone(); itr.next())
	{
		surface.setObject(itr.item());
	}

	const MMatrix surfaceMatrix = surface.transformationMatrix();
	const MBoundingBox surfaceBound = surface.boundingBox();

	///
	Stokes::Matrixf fieldMatrix;
	for (int i = 0; i < 4; ++ i)
	{
		for (int j = 0; j < 4; ++ j)
		{
			fieldMatrix.data[i * 4 + j] = surfaceMatrix(i, j);
		}
	}

	const MPoint surfaceBoundMin = surfaceBound.min();
	const MPoint surfaceBoundMax = surfaceBound.max();
	Stokes::Bound fieldBound(surfaceBoundMin.x, surfaceBoundMin.y, surfaceBoundMin.z, surfaceBoundMax.x, surfaceBoundMax.y, surfaceBoundMax.z);

	const Stokes::Vectorf displacedExtent(1, 1, 1);

	fieldBound.min -= displacedExtent;
	fieldBound.max += displacedExtent;

	Stokes::Vectoriu fieldDimension(512, 512, 512);
	Stokes::Integer32U fieldArity = 1;
	Stokes::SimpleFieldRef field(new Stokes::SimpleField(fieldMatrix, fieldBound, fieldDimension, fieldArity));

	///
	omp_set_num_threads(8);

	omp_lock_t lock;
	omp_init_lock(&lock);

	const int samples = 10000000;
	double* u = new double[samples];
	double* v = new double[samples];
	double* s = new double[samples];
	double* t = new double[samples];
	for (int i = 0; i < samples; ++ i)
	{
		u[i] = (double)rand() / (double)RAND_MAX;
		v[i] = (double)rand() / (double)RAND_MAX;
		s[i] = (double)rand() / (double)RAND_MAX;
		t[i] = (double)rand() / (double)RAND_MAX;
	}

	int i = 0;

	#pragma omp parallel private(i)
	{
		#pragma omp for
		for (i = 0; i < samples; ++ i)
		{
			MPoint p;
			MVector du, dv;

			omp_set_lock(&lock);
			surface.getDerivativesAtParm(u[i], v[i], p, du, dv, MSpace::kObject);
			omp_unset_lock(&lock);

			du.normalize();
			dv.normalize();
			MVector n = du ^ dv;

			Stokes::Vectorf noisedPoint(s[i], t[i], u[i]);
			Stokes::Float displacement = Stokes::Noiser::FractalBrownianMotion(noisedPoint, 0.5f, 16.5f, 8.0f, 0.5f) * 1.75f;
			Stokes::Vectorf displacementVector(n.x * displacement, n.y * displacement, n.z * displacement);

			Stokes::Vectorf localPoint(p.x, p.y, p.z);
			localPoint += displacementVector;

			Stokes::Vectorf worldPoint = Stokes::Transform(fieldMatrix, localPoint);

			Stokes::Vectoriu index;
			if (field->CalculateIndexFromWorldPoint(worldPoint, index))
			{
				Stokes::Float density = Stokes::Noiser::FractalBrownianMotion(noisedPoint, 1.0f, 8.0f, 1.0f, 0.5f) * 0.5f;
				if (density > 0)
				{
					omp_set_lock(&lock);
					field->Access(index)[0] += density;
					omp_unset_lock(&lock);
				}
			}
		}
	}

	///
	Stokes::Float* fieldData = field->Access(Stokes::Vectoriu(0, 0, 0));
	FILE* fp = fopen("NurbsSurface8.raw", "wb");
	fwrite(fieldData, field->GetSize(), 1, fp);
	fclose(fp);

	MLibrary::cleanup();
	return EXIT_SUCCESS;
}
