#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"


namespace glTF_2_0
{
	//-------------------------------------------------------------------------


	BufferViewT* const createBufferView(Document* const doc, const char* name)
	{
		auto instance = BufferView_t{new BufferViewT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->bufferViews.push_back(std::move(instance));
		return doc->root->bufferViews.back().get();
	}

	//---

	BufferViewT* const createBufferView(const uint8_t* const data, size_t length, Document* const doc, BufferT* const buf, const char* name)
	{
		KHUTILS_ASSERT_PTR(buf);

		auto view = createBufferView(doc);
		KHUTILS_ASSERT_PTR(view);

		view->buffer = getId(doc, buf);

		if (name)
		{
			view->name = name;
		}

		setBufferViewData(data, length, doc, view);

		return view;
	}

	//---

	BufferViewT* const createBufferView(const std::vector<uint8_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		return createBufferView(data.data(), data.size(), doc, buf);
	}

	//---

	size_t setBufferViewData(const uint8_t* const data, size_t length, Document* const doc, BufferViewT* const view)
	{
		KHUTILS_ASSERT_PTR(data);
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(view);
		KHUTILS_ASSERT_LESSEREQ(view->byteLength, 0);

		auto buf = getBuffer(doc, view->buffer);
		KHUTILS_ASSERT_PTR(buf);

		view->byteOffset = buf->byteLength;
		addBufferData(data, length, doc, buf);

		view->byteLength = length;
		view->byteStride = 0;
		view->target	 = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return view->byteLength;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
