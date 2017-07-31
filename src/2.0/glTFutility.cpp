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
