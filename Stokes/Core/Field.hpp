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

	Integer64U CalculateOffsetByBlockIndex(const Vectoriu& blockIndex);

	void Bind(const SemanticType semanticType, const WideString& semanticName, const ArrayRef& semanticArray);
	bool Query(const SemanticType semanticType);
	bool GetBinding(const SemanticType semanticType, WideString& rSemanticName, ArrayRef& rSemanticArray);
	void UnBind(const SemanticType semanticType);

protected:

	WideString                              mName;

	StorageMode                             mStorageMode;

	Vectoriu                                mTotalDim;
	Vectoriu                                mBlockDim;
	Vectoriu                                mTrueDim;

	typedef std::pair<WideString, ArrayRef> NamedArrayRef;
	std::map<SemanticType, NamedArrayRef>   mBindings;
};

typedef boost::shared_ptr<Field> FieldRef;

LEAVE_NAMESPACE_STOKES

#endif
