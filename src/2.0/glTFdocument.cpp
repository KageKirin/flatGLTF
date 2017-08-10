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

	std::unique_ptr<Document, decltype(&destroyDocument)> createDocumentPtr(const std::string& name)
	{
		return std::unique_ptr<Document, decltype(&destroyDocument)>{createDocument(name.c_str()), &destroyDocument};
	}

	//---

	bool verifyDocument(const Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(doc->root);
		auto& root = doc->root;

		auto viewOk = std::all_of(root->bufferViews.begin(), root->bufferViews.end(), [&](auto& view) {
			KHUTILS_ASSERT_PTR(view);
			return isValidBufferId(doc, view->buffer);
		});

		auto accOk = std::all_of(root->accessors.begin(), root->accessors.end(), [&](auto& acc) {
			KHUTILS_ASSERT_PTR(acc);
			return isValidBufferViewId(doc, acc->bufferView);
		});

		std::vector<AccessorT*> accessors;
		accessors.reserve(root->accessors.size());
		std::transform(root->accessors.begin(), root->accessors.end(), std::back_inserter(accessors), [](auto& acc) {
			return acc.get();
		});

		std::sort(accessors.begin(), accessors.end(), [](auto lhv, auto rhv) { return lhv->bufferView < rhv->bufferView; });
		accessors.resize(std::distance(accessors.begin(), std::unique(accessors.begin(), accessors.end(), [](auto lhv, auto rhv) { return lhv->bufferView == rhv->bufferView; })));
		auto uniqueBufferViews = accessors.size() == root->accessors.size();

		return viewOk && accOk && uniqueBufferViews;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
