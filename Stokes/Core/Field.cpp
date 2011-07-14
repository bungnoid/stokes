#include <Stokes/Core/Field.hpp>

ENTER_NAMESPACE_STOKES

Field::Field(const WideString& name, const Vectoriu& totalDim, const Vectoriu& blockDim) :
	mName(name),
	mTotalDim(totalDim),
	mBlockDim(blockDim)
{
}

Field::~Field()
{
}

void Field::AddAttribute(const WideString& attributeName, const ATTRIBUTE_SCALAR attributeType, const ArrayRef array)
{
	mAttributeTypes.insert(std::make_pair(attributeName, attributeType));
	mAttributeArrays.insert(std::make_pair(attributeName, array));
}

bool Field::GetAttribute(const WideString& attributeName, AttributeType& attributeType, ArrayRef& array)
{
	std::map<WideString, AttributeType>::iterator atItr = mAttributeTypes.find(attributeName);
	if (atItr != mAttributeTypes.end())
	{
		std::map<WideString, ArrayRef>::iterator aaItr = mAttributeArrays.find(attributeName);
		assert(aaItr != mAttributeArrays.end());
		
		attributeType = atItr->second;
		array = aaItr->second;
		
		return true;
	}
	
	return false;
}

void Fill(const Emitter& emitter);

LEAVE_NAMESPACE_STOKES
