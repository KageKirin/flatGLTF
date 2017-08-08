#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/common/glTFutils.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	using namespace glTF_common;

	//-------------------------------------------------------------------------

	BufferT* const createBuffer(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto instance = Buffer_t{new BufferT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->buffers.push_back(std::move(instance));
		createBufferData(doc, instance.get()).clear();
		return doc->root->buffers.back().get();
	}

	//---

	BufferT* const createBuffer(Document* const doc, const char* uri, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(uri);

		auto buffer = createBuffer(doc, name);
		buffer->uri = uri;

		if (isDataUri(buffer->uri))
		{
			setBufferData(convertUriToData(uri), doc, buffer);
			buffer->uri = setUriBase64(uri, "");	// remove data, as its decoded in buffer now
		}

		return buffer;
	}

	//---

	///-----------------------------------------------------------------------
	/// bindata
	///-----------------------------------------------------------------------

	std::vector<uint8_t>& createBufferData(Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(buf);

		doc->bindata[buf].clear();
		return doc->bindata[buf];
	}

	//---

	std::vector<uint8_t>& getBufferData(Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(buf);

		auto id = getId(doc, buf);
		KHUTILS_ASSERT(isValidBufferId(doc, id));

		auto it = std::find_if(doc->bindata.begin(), doc->bindata.end(), [&](auto& bdp) { return bdp.first == buf; });
		KHUTILS_ASSERT_NOT(it, doc->bindata.end());

		return it->second;
	}

	//---
	// sets buffer data, overwriting existing
	// returns new size
	// returns 0 if: buffer does not exist

	size_t setBufferData(const std::vector<uint8_t>& data, Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return setBufferData(data.data(), data.size(), doc, buf);
	}

	//---

	size_t setBufferData(const uint8_t* data, size_t length, Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(buf);

		auto id = getId(doc, buf);
		if (isValidBufferId(doc, id))
		{
			auto bufdata = getBufferData(doc, buf);
			bufdata.clear();
			bufdata.reserve(length);
			std::copy_n(data, length, std::back_inserter(bufdata));
			return getBufferData(doc, buf).size();
		}

		return 0;
	}

	//---
	// appends buffer data to existing buffer data
	// returns new size
	// returns 0 if: buffer does not exist

	size_t appendBufferData(const std::vector<uint8_t>& data, Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return appendBufferData(data.data(), data.size(), doc, buf);
	}

	//---

	size_t appendBufferData(const uint8_t* data, size_t length, Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(buf);

		auto id = getId(doc, buf);
		if (isValidBufferId(doc, id))
		{
			auto bufdata = getBufferData(doc, buf);
			bufdata.reserve(bufdata.size() + length);
			std::copy_n(data, length, std::back_inserter(bufdata));
			return getBufferData(doc, buf).size();
		}

		return 0;
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
