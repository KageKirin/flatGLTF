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

	size_t setBufferViewData(const std::vector<uint8_t>& data, Document* const doc, BufferViewT* const view)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return setBufferViewData(data.data(), data.size(), doc, view);
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
		appendBufferData(data, length, doc, buf);

		view->byteLength = length;
		view->byteStride = 0;

		return view->byteLength;
	}

	//---

	std::vector<uint8_t> getBufferViewData(const Document* const doc, const BufferViewT* const view)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(view);

		auto buf = getBuffer(doc, view->buffer);
		KHUTILS_ASSERT_PTR(buf);

		auto bufdata = getBufferData(doc, buf);

		std::vector<uint8_t> viewdata;
		viewdata.reserve(view->byteLength);
		std::copy_n(bufdata.begin() + view->byteOffset, view->byteLength, std::back_inserter(viewdata));
		return viewdata;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
