#ifndef FIELD_HPP
#define FIELD_HPP

#include <map>

#include <boost/shared_ptr.hpp>

#include <Stokes/Core/Array.hpp>
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

	enum SemanticType
	{
		SEMANTIC_AGE,
		SEMANTIC_COLOR,
		SEMANTIC_DENSITY,
		SEMANTIC_NORMAL,
		SEMANTIC_OPACITY,
		SEMANTIC_POSITION,
		SEMANTIC_TEMPERATURE
	};

	static const WideString& GetStorageModeAsString(const StorageMode storageMode);

	static const WideString& GetSemanticTypeAsString(const SemanticType semanticType);

	static Integer32U GetSemanticTypeArity(const SemanticType semanticType);

public:

	Field(const WideString& name, const Vectoriu& totalDim);
	Field(const WideString& name, const Vectoriu& totalDim, const Vectoriu& blockDim);
	virtual ~Field();

	StorageMode GetStorageMode() const;

	const Vectoriu& GetTotalDim() const;
	const Vectoriu& GetBlockDim() const;
	const Vectoriu& GetTrueDim() const;
	
	void BindAttribute(const WideString& name, const SemanticType type, const ArrayRef& array);
	bool QueryAttribute(const WideString& name, SemanticType& rType, ArrayRef& rArray);
	void UnBindAttribute(const WideString& name);

protected:

	WideString                         mName;

	StorageMode                        mStorageMode;

	Vectoriu                           mTotalDim;
	Vectoriu                           mBlockDim;
	Vectoriu                           mTrueDim;

	std::map<WideString, SemanticType> mAttributeTypes;
	std::map<WideString, ArrayRef>     mAttributeArrays;
};

typedef boost::shared_ptr<Field> FieldRef;

LEAVE_NAMESPACE_STOKES

#endif
