#ifndef FIELD_HPP
#define FIELD_HPP

#include <map>

#include <boost/shared_ptr.hpp>

#include <Stokes/Core/Array.hpp>
#include <Stokes/Core/Bound.hpp>
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
		SEMANTIC_TEMPERATURE,
		SEMANTIC_VELOCITY
	};

	static const WideString& GetStorageModeAsString(const StorageMode storageMode);

	static const WideString& GetSemanticTypeAsString(const SemanticType semanticType);

	static Integer32U GetSemanticTypeArity(const SemanticType semanticType);

public:

	Field(const WideString& name, const Bound& bound, const Vectoriu& globalDim);
	Field(const WideString& name, const Bound& bound, const Vectoriu& globalDim, const Vectoriu& blockDim);
	virtual ~Field();

	StorageMode GetStorageMode() const;

	const Vectoriu& GetGlobalDim() const;
	const Vectoriu& GetBlockDim() const;

	/**
	 * @param index Transform global index to the position in world whenever field is slice-based or field-based.g
	 */
	Vectorf ConvertGlobalIndexToWorldPosition(const Vectoriu& globalindex);

	void Bind(const SemanticType semanticType, const WideString& semanticAlias, const ArrayRef& semanticArray);
	bool Query(const SemanticType semanticType);
	bool GetBinding(const SemanticType semanticType, WideString& rSemanticAlias, ArrayRef& rSemanticArray);
	void UnBind(const SemanticType semanticType);

protected:

	WideString                              mName;

	Bound                                   mBound;

	Vectoriu                                mGlobalDim;
	Vectoriu                                mBlockDim;

	StorageMode                             mStorageMode;

	typedef std::pair<WideString, ArrayRef> NamedArrayRef;
	std::map<SemanticType, NamedArrayRef>   mBindings;
};

typedef boost::shared_ptr<Field> FieldRef;

LEAVE_NAMESPACE_STOKES

#endif
