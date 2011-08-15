#include <omp.h>

#include <boost/random.hpp>

#include <maya/MBoundingBox.h>
#include <maya/MFileIO.h>
#include <maya/MFnNurbsSurface.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MMatrix.h>
#include <maya/MPlug.h>
#include <maya/MPoint.h>

#include <Stokes/Core/Bound.hpp>
#include <Stokes/Core/Noiser.hpp>
#include <Stokes/Core/Random.hpp>

#include <Stokes/Maya/NurbsSurfaceEmitter.hpp>

ENTER_NAMESPACE_STOKES_MAYA

NurbsSurfaceEmitter::NurbsSurfaceEmitter(const MObject& object) :
	ObjectEmitter(object)
{
	assert(mObject.hasFn(MFn::kNurbsSurface));
}

NurbsSurfaceEmitter::~NurbsSurfaceEmitter()
{
}

void NurbsSurfaceEmitter::CalculateWorldBound(Bound& bound) const
{
	MFnNurbsSurface surface(mObject);
	const MBoundingBox& surfaceBound = surface.boundingBox();
	const MPoint& min = surfaceBound.min();
	const MPoint& max = surfaceBound.max();

	bound.min.x = static_cast<Float>(min.x) - mDisplacedAmplitude;
	bound.min.y = static_cast<Float>(min.y) - mDisplacedAmplitude;
	bound.min.z = static_cast<Float>(min.z) - mDisplacedAmplitude;
	bound.max.x = static_cast<Float>(max.x) + mDisplacedAmplitude;
	bound.max.y = static_cast<Float>(max.y) + mDisplacedAmplitude;
	bound.max.z = static_cast<Float>(max.z) + mDisplacedAmplitude;
}

void NurbsSurfaceEmitter::Fill(const FieldRef& field)
{
	assert(mObject.hasFn(MFn::kNurbsSurface));
	assert(field);

	// Process Maya DG node.
	//
	MFnNurbsSurface surface(mObject);

	// Get the range for U and V.
	MPlug minValueUPlug = surface.findPlug("minValueU");
	MPlug maxValueUPlug = surface.findPlug("maxValueU");
	MPlug minValueVPlug = surface.findPlug("minValueV");
	MPlug maxValueVPlug = surface.findPlug("maxValueV");

	const Double minValueU = minValueUPlug.asDouble();
	const Double maxValueU = maxValueUPlug.asDouble();
	const Double minValueV = minValueVPlug.asDouble();
	const Double maxValueV = maxValueVPlug.asDouble();

	const Double valueURange = maxValueU - minValueU;
	const Double valueVRange = maxValueV - minValueV;
	const Double valueUVRatio = valueURange / valueVRange;

	// sampleCountU * sampleCountV = mSamples;
	// sampleCountU / sampleCountV = valueURange / valueVRange
	// sampleCountU = valueUVRatio * sampleCountV
	// sampleCountV ^ 2 * valueUVRatio = mSamples;
	const Integer32U sampleV = static_cast<Integer32U>(sqrt(mSample / valueUVRatio));
	const Integer32U sampleU = mSample / sampleV;

	const Double deltaU = valueURange / sampleU;
	const Double deltaV = valueVRange / sampleV;

	// Fill field in MT.
	//
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

			Double u = Random::NextAsDouble() * valueURange + minValueU;
			Double v = Random::NextAsDouble() * valueVRange + minValueV;
			Vectorf noisedPoint(static_cast<Float>(u) * mScale.x - mOffset.x, Random::NextAsFloat() * mScale.y - mOffset.y, static_cast<Float>(v) * mScale.z - mOffset.z);

			surface.getDerivativesAtParm(u, v, p, du, dv, MSpace::kWorld);
			omp_unset_lock(&lock);

			// Displace the sample along normal.
			du.normalize();
			dv.normalize();
			MVector n = du ^ dv;
			
			Stokes::Float displacement = Stokes::Noiser::FractalBrownianMotion(noisedPoint, mDisplacedH, mDisplacedLacunarity, mDisplacedOctave) * mDisplacedAmplitude;
			n *= displacement;
			p += n;
			Vectorf worldPoint(p.x, p.y, p.z);

			// Fill the density.
			Vectoriu index;
			if (field->CalculateIndexFromWorldPoint(worldPoint, index))
			{
				Stokes::Float density = Stokes::Noiser::FractalBrownianMotion(noisedPoint, mH, mLacunarity, mOctave) * mAmplitude;
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

LEAVE_NAMESPACE_STOKES_MAYA
