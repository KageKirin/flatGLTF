#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"


namespace glTF_2_0
{
	///-----------------------------------------------------------------------
	/// utility
	///-----------------------------------------------------------------------

	/// clone a document into a new one
	bool cloneDocument(const Document* const source, Document* const target)
	{
		KHUTILS_ASSERT_PTR(source);
		KHUTILS_ASSERT_PTR(target);

		auto newRoot = from_flatbuffer_internal(to_flatbuffer(source->root));
		target->root.swap(newRoot);
		target->bindata.clear();
		std::copy(source->bindata.begin(),
				  source->bindata.end(),
				  std::insert_iterator<decltype(target->bindata)>(target->bindata, target->bindata.end()));

		return true;
	}


	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	bool binarizeDocument(Document* const doc)
	{
		return false;
	}

	//---

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	bool embedDocument(Document* const doc)
	{
		return false;
	}

	//---

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	bool dislodgeDocument(Document* const doc)
	{
		return false;
	}

	//---

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	bool splitDocument(Document* const doc)
	{
		return false;
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
