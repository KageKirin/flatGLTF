#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

#include <memory>

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	AssetT* createAsset_default(const char* name);

	Document* const createDocument(const char* name)
	{
		auto instance		  = std::unique_ptr<Document>{new Document};
		instance->root		  = Root_t{new RootT};
		instance->root->asset = Asset_t{createAsset_default(name)};

		return instance.release();
	}

	//---

	void destroyDocument(Document* const doc)
	{
		if (doc)
		{
			delete doc;
		}
	}

	//---

	// document creation

	std::unique_ptr<Document, decltype(&destroyDocument)> createDocument(const std::string& name)
	{
		return std::unique_ptr<Document, decltype(&destroyDocument)>{createDocument(name.c_str()), &destroyDocument};
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
