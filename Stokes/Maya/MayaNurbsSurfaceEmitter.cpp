#include <omp.h>

#include <boost/random.hpp>

#include <maya/MBoundingBox.h>
#include <maya/MFileIO.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MPoint.h>

#include <Stokes/Core/Bound.hpp>
#include <Stokes/Core/Noiser.hpp>
#include <Stokes/Core/Random.hpp>

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

	bound.min.x = static_cast<Float>(min.x) - mNoiseAmplitudeDisplaced;
	bound.min.y = static_cast<Float>(min.y) - mNoiseAmplitudeDisplaced;
	bound.min.z = static_cast<Float>(min.z) - mNoiseAmplitudeDisplaced;
	bound.max.x = static_cast<Float>(max.x) + mNoiseAmplitudeDisplaced;
	bound.max.y = static_cast<Float>(max.y) + mNoiseAmplitudeDisplaced;
	bound.max.z = static_cast<Float>(max.z) + mNoiseAmplitudeDisplaced;
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

	#pragma omp parallel private(i)
	{
		#pragma omp for
		for (i = 0; i < static_cast<int>(mSample); ++ i)
		{
			MPoint p;
			MVector du, dv;

			// MFnNurbsSurface::getDerivativesAtParm is not thread-safe.
			omp_set_lock(&lock);

			Double u = Random::NextAsDouble();
			Double v = Random::NextAsDouble();
			Vectorf noisedPoint(Random::NextAsFloat(), static_cast<Float>(u), Random::NextAsFloat());

			surface.getDerivativesAtParm(u, v, p, du, dv, MSpace::kObject);
			omp_unset_lock(&lock);

			// Displace the sample along normal.
			du.normalize();
			dv.normalize();
			MVector n = du ^ dv;
			
			Stokes::Float displacement = Stokes::Noiser::FractalBrownianMotion(noisedPoint, mNoiseHDisplaced, mNoiseLacunarityDisplaced, mNoiseOctaveDisplaced) * mNoiseAmplitudeDisplaced;
			n *= displacement;
			p += n;
			Stokes::Vectorf localPoint(static_cast<Float>(p.x), static_cast<Float>(p.y), static_cast<Float>(p.z));

			Stokes::Vectorf worldPoint = Stokes::Transform(localToWorld, localPoint);

			// Fill the density.
			Stokes::Vectoriu index;
			if (field->CalculateIndexFromWorldPoint(worldPoint, index))
			{
				Stokes::Float density = Stokes::Noiser::FractalBrownianMotion(noisedPoint, mNoiseH, mNoiseLacunarity, mNoiseOctave) * mNoiseAmplitude;
				if (density > 0.0f)
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
