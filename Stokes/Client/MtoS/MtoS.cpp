#include <omp.h>

#include <boost/random.hpp>

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

	//
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

	int i = 0;
	const int samples = 100000000;

	boost::random::mt19937 seed;
	boost::uniform_real<> dist(0.0, 1.0);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<> > rng(seed, dist);

	#pragma omp parallel private(i)
	{
		#pragma omp for
		for (i = 0; i < samples; ++ i)
		{
			MPoint p;
			MVector du, dv;

			// MFnNurbsSurface::getDerivativesAtParm is not thread-safe.
			omp_set_lock(&lock);

			double u = rng();
			double v = rng();
			Stokes::Vectorf noisedPoint(rng() * 16, rng() * 16, u * 16);

			surface.getDerivativesAtParm(u, v, p, du, dv, MSpace::kObject);
			omp_unset_lock(&lock);

			// Displace the sample along normal.
			du.normalize();
			dv.normalize();
			MVector n = du ^ dv;
			
			Stokes::Float displacement = Stokes::Noiser::FractalBrownianMotion(noisedPoint, 0.5f, 4.5f, 3.0f, 0.5f);
			Stokes::Vectorf localPoint(p.x + n.x * displacement, p.y + n.y * displacement, p.z + n.z * displacement);

			Stokes::Vectorf worldPoint = Stokes::Transform(fieldMatrix, localPoint);

			// Fill the density.
			Stokes::Vectoriu index;
			if (field->CalculateIndexFromWorldPoint(worldPoint, index))
			{
				Stokes::Float density = Stokes::Noiser::FractalBrownianMotion(noisedPoint, 0.5f, 8.0f, 1.0f, 0.5f);
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
	FILE* fp = fopen("NurbsSurfaceMT10M.raw", "wb");
	fwrite(fieldData, field->GetSize(), 1, fp);
	fclose(fp);

	MLibrary::cleanup();
	return EXIT_SUCCESS;
}
