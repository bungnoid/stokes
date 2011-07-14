#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

Integer32U Field::GetSemanticTypeArity(const SemanticType semanticType)
{
	switch(semanticType)
	{
		case SEMANTIC_AGE:
		case SEMANTIC_DENSITY:
		case SEMANTIC_OPACITY:
		case SEMANTIC_TEMPERATURE:
			return 1;

		case SEMANTIC_COLOR:
		case SEMANTIC_NORMAL:
		case SEMANTIC_POSITION:
			return 3;
	}

	return 0;
}

Field::Field(const WideString& name, const Vectoriu& totalDim) :
	mName(name),
	mStorageMode(STORAGE_SLICE),
	mTotalDim(totalDim)
{
}

Field::Field(const WideString& name, const Vectoriu& totalDim, const Vectoriu& blockDim) :
	mName(name),
	mStorageMode(STORAGE_BLOCK),
	mTotalDim(totalDim),
	mBlockDim(blockDim)
{
}

Field::~Field()
{
}

Field::StorageMode Field::GetStorageMode() const
{
	return mStorageMode;
}

const Vectoriu& Field::GetTotalDim() const
{
	return mTotalDim;
}

const Vectoriu& Field::GetBlockDim() const
{
	return mBlockDim;
}

const Vectoriu& Field::GetTrueDim() const
{
	return mTrueDim;
}

void Field::BindAttribute(const WideString& attributeName, const SemanticType attributeType, const ArrayRef& array)
{
	mAttributeTypes.insert(std::make_pair(attributeName, attributeType));
	mAttributeArrays.insert(std::make_pair(attributeName, array));
}

bool Field::QueryAttribute(const WideString& name, SemanticType& rType, ArrayRef& rArray)
{
	std::map<WideString, SemanticType>::iterator stItr = mAttributeTypes.find(name);
	if (stItr != mAttributeTypes.end())
	{
		std::map<WideString, ArrayRef>::iterator aItr = mAttributeArrays.find(name);

		rType = stItr->second;
		rArray = aItr->second;

		return true;
	}

	return false;
}

void Field::UnBindAttribute(const WideString& name)
{
	mAttributeTypes.erase(name);
	mAttributeArrays.erase(name);
}

LEAVE_NAMESPACE_STOKES
