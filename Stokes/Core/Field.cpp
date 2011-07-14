#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

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

void Field::BindAttribute(const WideString& attributeName, const SemanticType attributeType, const ArrayRef& array)
{
	mAttributeTypes.insert(std::make_pair(attributeName, attributeType));
	mAttributeArrays.insert(std::make_pair(attributeName, array));
}

void Field::UnBindAttribute(const WideString& name)
{
	mAttributeTypes.erase(name);
	mAttributeArrays.erase(name);
}

LEAVE_NAMESPACE_STOKES
