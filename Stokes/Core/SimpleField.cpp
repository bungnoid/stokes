#include <Stokes/Core/SimpleField.hpp>

ENTER_NAMESPACE_STOKES

SimpleField::SimpleField(const Matrixf& localToWorld, const Bound& bound, const Vectoriu& dimension, const Integer32U arity) :
	Field(localToWorld, bound, dimension, arity),
	mAddresses(NULL),
	mAddressCount(0)
{
	mAddresses = (void**)malloc(mDimension.z * sizeof(void*));
	assert(mAddresses);
	memset(mAddresses, 0, mDimension.z * sizeof(void*));

	size_t sliceSize = mDimension.x * mDimension.y * mArity * sizeof(Float);
	for (Integer32U z = 0; z < mDimension.z; ++ z)
	{
		mAddresses[z] = malloc(sliceSize);
		assert(mAddresses[z]);
		memset(mAddresses[z], 0, sliceSize);
	}
}

SimpleField::~SimpleField()
{
	for (Integer32U z = 0; z < mDimension.z; ++ z)
	{
		if (mAddresses[z])
		{
			free(mAddresses[z]);
		}
	}
	free(mAddresses);
}

Float* SimpleField::Access(const Vectoriu& index)
{
	const Integer32U linearIndexInSlice = (mDimension.x * index.y + index.x) * mArity;
	return (reinterpret_cast<Float*>(mAddresses[index.z]) + linearIndexInSlice);
}

bool SimpleField::Save(const WideString& path, const bool compress)
{
	FILE* fp = _wfopen(path.c_str(), L"wb");
	if (!fp)
	{
		return false;
	}

	size_t sliceSize = mDimension.x * mDimension.y * mArity * sizeof(Float);
	void* blankSlice = malloc(sliceSize);
	assert(blankSlice);
	memset(blankSlice, 0, sliceSize);

	for (Integer32U z = 0; z < mDimension.z; ++ z)
	{
		if (mAddresses[z])
		{
			fwrite(mAddresses[z], sliceSize, 1, fp);
		}
		else
		{
			fwrite(blankSlice, sliceSize, 1, fp);
		}
	}
	fflush(fp);
	fclose(fp);

	return true;
}

LEAVE_NAMESPACE_STOKES
