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
		case SEMANTIC_VELOCITY:
			return 3;
	}

	return 0;
}

Field::Field(const WideString& name, const Bound& bound, const Vectoriu& globalDim) :
	mName(name),
	mBound(bound),
	mGlobalDim(globalDim),
	mStorageMode(STORAGE_SLICE)
{
}

Field::Field(const WideString& name, const Bound& bound, const Vectoriu& globalDim, const Vectoriu& blockDim) :
	mName(name),
	mBound(bound),
	mGlobalDim(globalDim),
	mBlockDim(blockDim),
	mStorageMode(STORAGE_BLOCK)
{
	mGlobalDim.x = mGlobalDim.x / mBlockDim.x * mBlockDim.x;
	mGlobalDim.y = mGlobalDim.y / mBlockDim.y * mBlockDim.y;
	mGlobalDim.z = mGlobalDim.z / mBlockDim.z * mBlockDim.z;
}

Field::~Field()
{
}

Field::StorageMode Field::GetStorageMode() const
{
	return mStorageMode;
}

const Vectoriu& Field::GetGlobalDim() const
{
	return mGlobalDim;
}

const Vectoriu& Field::GetBlockDim() const
{
	return mBlockDim;
}

Vectorf Field::ConvertGlobalIndexToWorldPosition(const Vectoriu& globalIndex)
{
	const Vectorf& fieldSize = mBound.Size();
	const Vectorf voxelSize(fieldSize.x / mGlobalDim.x, fieldSize.y / mGlobalDim.y, fieldSize.z / mGlobalDim.z);
	return Vectorf(voxelSize.x * (globalIndex.x + 0.5f), voxelSize.y * (globalIndex.y + 0.5f), voxelSize.z * (globalIndex.z + 0.5f));
}

void Field::Bind(const SemanticType semanticType, const WideString& semanticAlias, const ArrayRef& semanticArray)
{
	assert(semanticArray->GetDataType() == DATA_TYPE_FLOAT);
	mBindings.insert(std::make_pair(semanticType, std::make_pair(semanticAlias, semanticArray)));
}

bool Field::Query(const SemanticType semanticType)
{
	return (mBindings.find(semanticType) != mBindings.end());
}

bool Field::GetBinding(const SemanticType semanticType, WideString& rSemanticAlias, ArrayRef& rSemanticArray)
{
	std::map<SemanticType, NamedArrayRef>::iterator itr = mBindings.find(semanticType);
	if (itr != mBindings.end())
	{
		rSemanticAlias = itr->second.first;
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
