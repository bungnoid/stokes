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

void Field::Bind(const SemanticType semanticType, const WideString& semanticName, const ArrayRef& semanticArray)
{
	mBindings.insert(std::make_pair(semanticType, std::make_pair(semanticName, semanticArray)));
}

bool Field::Query(const SemanticType semanticType)
{
	return (mBindings.find(semanticType) != mBindings.end());
}

bool Field::GetBinding(const SemanticType semanticType, WideString& rSemanticName, ArrayRef& rSemanticArray)
{
	std::map<SemanticType, NamedArrayRef>::iterator itr = mBindings.find(semanticType);
	if (itr != mBindings.end())
	{
		rSemanticName = itr->second.first;
		rSemanticArray = itr->second.second;

		return true;
	}

	return false;
}

void Field::UnBind(const SemanticType semanticType)
{
	mBindings.erase(semanticType);
}

LEAVE_NAMESPACE_STOKES
