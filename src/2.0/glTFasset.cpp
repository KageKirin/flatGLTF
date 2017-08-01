#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	AssetT* createAsset_default(const char* name)
	{
		auto instance		 = Asset_t{new AssetT};
		instance->name		 = name;
		instance->version	= "2.0";
		instance->minVersion = "2.0";
		instance->copyright  = "NONE, unless specified otherwise";
		instance->generator  = "flatgltf, unless specified otherwise";
		return instance.release();
	}

	///-----------------------------------------------------------------------
	/// simple get for unique elements
	///-----------------------------------------------------------------------

	AssetT* const getAsset(const Document* const doc)
	{
		return (doc && doc->root) ? doc->root->asset.get() : nullptr;
	}

	//---

	SceneT* const getMainScene(const Document* const doc)
	{
		return (doc && doc->root) ? getScene(doc, doc->root->scene) : nullptr;
	}

	//---

	void setMainScene(Document* const doc, SceneT* const scene)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(scene);
		setMainScene(doc, getId(doc, scene));
	}

	//---

	void setMainScene(Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_GREATEREQ(id, 0);
		doc->root->scene = id;
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
