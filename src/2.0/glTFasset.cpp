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

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
