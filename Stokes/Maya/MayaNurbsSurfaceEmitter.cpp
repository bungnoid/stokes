#include <omp.h>

#include <boost/random.hpp>

#include <maya/MBoundingBox.h>
#include <maya/MFileIO.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MPoint.h>

#include <Stokes/Core/Bound.hpp>
#include <Stokes/Core/Noiser.hpp>

#include <Stokes/Maya/MayaNurbsSurfaceEmitter.hpp>

ENTER_NAMESPACE_STOKES

MayaNurbsSurfaceEmitter::MayaNurbsSurfaceEmitter(const MObject& mayaObject) :
	MayaObjectEmitter(mayaObject)
{
}

MayaNurbsSurfaceEmitter::~MayaNurbsSurfaceEmitter()
{
}

void MayaNurbsSurfaceEmitter::CalculateWorldBound(Bound& bound) const
{
	assert(mMayaObject.hasFn(MFn::kNurbsSurface));

	MFnNurbsSurface surface(mMayaObject);
	const MBoundingBox& surfaceBound = surface.boundingBox();
	const MPoint& min = surfaceBound.min();
	const MPoint& max = surfaceBound.max();

	bound.min.x = static_cast<Float>(min.x);
	bound.min.y = static_cast<Float>(min.y);
	bound.min.z = static_cast<Float>(min.z);
	bound.max.x = static_cast<Float>(max.x);
	bound.max.y = static_cast<Float>(max.y);
	bound.max.z = static_cast<Float>(max.z);
}

void MayaNurbsSurfaceEmitter::Fill(const FieldRef& field)
{
	assert(mMayaObject.hasFn(MFn::kNurbsSurface));

	MFnNurbsSurface surface(mMayaObject);

	const Matrixf& localToWorld = field->GetLocalToWorld();

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
			Vectorf noisedPoint(static_cast<Float>(rng()), static_cast<Float>(rng()), static_cast<Float>(u));

			surface.getDerivativesAtParm(u, v, p, du, dv, MSpace::kObject);
			omp_unset_lock(&lock);

			// Displace the sample along normal.
			du.normalize();
			dv.normalize();
			MVector n = du ^ dv;
			
			Stokes::Float displacement = Stokes::Noiser::FractalBrownianMotion(noisedPoint, 0.5f, 4.5f, 3.0f, 0.5f);
			n *= displacement;
			p += n;
			Stokes::Vectorf localPoint(static_cast<Float>(p.x), static_cast<Float>(p.y), static_cast<Float>(p.z));

			Stokes::Vectorf worldPoint = Stokes::Transform(localToWorld, localPoint);

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
}

LEAVE_NAMESPACE_STOKES
