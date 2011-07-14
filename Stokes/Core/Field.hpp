#ifndef FIELD_HPP
#define FIELD_HPP

#include <map>

#include <Stokes/Core/Array.hpp>
#include <Stokes/Core/Emitter.hpp>
#include <Stokes/Core/Matrix.hpp>
#include <Stokes/Core/Vector.hpp>

ENTER_NAMESPACE_STOKES

class STOKES_API Field
{
public:
	enum StorageMode
	{
		STORAGE_BLOCK,
		STORAGE_SLICE,
	};

	enum AttributeType
	{
		ATTRIBUTE_HALF,
		ATTRIBUTE_HALF2,
		ATTRIBUTE_HALF3,
		ATTRIBUTE_HALF4,
	
		ATTRIBUTE_FLOAT,
		ATTRIBUTE_FLOAT2,
		ATTRIBUTE_FLOAT3,
		ATTRIBUTE_FLOAT4,
		
		ATTRIBUTE_DOUBLE,
		ATTRIBUTE_DOUBLE2,
		ATTRIBUTE_DOUBLE3,
		ATTRIBUTE_DOUBLE4,
	};

	Field(const WideString& fieldName, const Vectoriu& totalDim);
	Field(const WideString& fieldName, const Vectoriu& totalDim, const Vectoriu& blockDim);
	virtual ~Field();
	
	void AddAttribute(const WideString& attributeName, const ATTRIBUTE_SCALAR attributeType, const ArrayRef array);
	bool GetAttribute(WideString& attributeName, AttributeType& attributeType, ArrayRef& array);

protected:

	WideString                          mName;

	Vectoriu                            mTotalDim;
	Vectoriu                            mBlockDim;

	std::map<WideString, AttributeType> mAttributeTypes;
	std::map<WideString, ArrayRef>      mAttributeArrays;
};

LEAVE_NAMESPACE_STOKES

#endif
