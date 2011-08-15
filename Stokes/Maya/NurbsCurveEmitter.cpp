#include <maya/MBoundingBox.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MPlug.h>

#include <Stokes/Core/Noiser.hpp>
#include <Stokes/Core/Random.hpp>
#include <Stokes/Core/Vector.hpp>

#include <Stokes/Maya/NurbsCurveEmitter.hpp>

ENTER_NAMESPACE_STOKES_MAYA

NurbsCurveEmitter::NurbsCurveEmitter(const MObject& object) :
	ObjectEmitter(object)
{
	assert(object.hasFn(MFn::kNurbsCurve));
}

NurbsCurveEmitter::~NurbsCurveEmitter()
{
}

void NurbsCurveEmitter::CalculateWorldBound(Bound& bound) const
{
	MFnNurbsCurve curve(mObject);
	const MBoundingBox& curveBound = curve.boundingBox();
	const MPoint& min = curveBound.min();
	const MPoint& max = curveBound.max();

	bound.min.x = static_cast<Float>(min.x) - mDisplacedAmplitude;
	bound.min.y = static_cast<Float>(min.y) - mDisplacedAmplitude;
	bound.min.z = static_cast<Float>(min.z) - mDisplacedAmplitude;
	bound.max.x = static_cast<Float>(max.x) + mDisplacedAmplitude;
	bound.max.y = static_cast<Float>(max.y) + mDisplacedAmplitude;
	bound.max.z = static_cast<Float>(max.z) + mDisplacedAmplitude;
}

void NurbsCurveEmitter::Fill(const FieldRef& field)
{
	MFnNurbsCurve curve(mObject);

	// Get the range for U and V.
	MPlug minValuePlug = curve.findPlug("minValue");
	MPlug maxValuePlug = curve.findPlug("maxValue");

	const Double minValue = minValuePlug.asDouble();
	const Double maxValue = maxValuePlug.asDouble();

	const Double valueRange = maxValue - minValue;

	int i = 0;
	for (i = 0; i < static_cast<int>(mSample); ++ i)
	{
		double u = Stokes::Random::NextAsDouble();
		double v = Stokes::Random::NextAsDouble();
		double w = Stokes::Random::NextAsDouble();

		double param = u * valueRange + minValue;

		MPoint p;
		curve.getPointAtParam(param, p, MSpace::kWorld);
		MVector t = curve.tangent(param, MSpace::kWorld);
		t.normalize();
		MVector n = curve.normal(param, MSpace::kWorld);
		n.normalize();
		MVector b = n ^ t;

		double r = sqrt(v);
		double phi = w * 2.0 * M_PI;
		double x = r * cos(phi);
		double y = r * sin(phi);

		// TODO: No radius here.
		MPoint newP = p + n * x + b * y;

		MVector radialDirection = newP - p;
		radialDirection.normalize();
		
		Stokes::Vectorf noisedPoint(Random::NextAsFloat() * mScale.x - mOffset.x, Random::NextAsFloat() * mScale.y - mOffset.y, static_cast<Float>(u) * mScale.z - mOffset.z);
		Float displacement = Stokes::Noiser::FractalBrownianMotion(noisedPoint, mDisplacedH, mDisplacedLacunarity, mDisplacedOctave) * mDisplacedAmplitude;
		MPoint displacedP = newP + radialDirection * displacement;
		Stokes::Vectorf worldPoint(static_cast<Stokes::Float>(displacedP.x), static_cast<Stokes::Float>(displacedP.y), static_cast<Stokes::Float>(displacedP.z));

		Stokes::Vectoriu index;
		if (field->CalculateIndexFromWorldPoint(worldPoint, index))
		{
			Float density = Stokes::Noiser::FractalBrownianMotion(noisedPoint, mH, mLacunarity, mOctave) * mAmplitude;
			if (density > 0)
			{
				field->Access(index)[0] += density;
			}
		}
	}
}

LEAVE_NAMESPACE_STOKES_MAYA
