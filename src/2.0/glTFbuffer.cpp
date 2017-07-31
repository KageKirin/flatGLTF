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
		auto instance = Buffer_t{new BufferT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->buffers.push_back(std::move(instance));
		return doc->root->buffers.back().get();
	}

	//---

	//! create buffer
	// if name is null, data will be internal
	BufferT* const createBuffer(Document* const doc, const char* uri, const char* name)
	{
		auto buffer = createBuffer(doc, name);
		if (uri)
		{
			createBindata(doc, uri);
		}
		else
		{
		}

		return buffer;
	}

	//---

	std::vector<uint8_t>& createBindata(Document* const doc, const char* name)
	{
		return getBindata(doc, name);
	}

	//---

	size_t addBufferData(const uint8_t* const data, size_t length, Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_PTR(data);
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(buf);

		if (isDataUri(buf->uri))
		{
			auto bufData = convertUriToData(buf->uri);
			std::copy_n(data, length, std::back_inserter(bufData));
			buf->uri		= convertDataToUri(bufData);
			buf->byteLength = bufData.size();
		}
		else
		{
			auto& bufData = getBindata(doc, buf->uri.c_str());
			std::copy_n(data, length, std::back_inserter(bufData));
			buf->byteLength = bufData.size();
		}
		return buf->byteLength;
	}


	///-----------------------------------------------------------------------
	/// bindata
	///-----------------------------------------------------------------------

	std::vector<uint8_t>& getBindata(Document* const doc, const char* name)
	{
		return doc->bindata[name];
	}

	size_t setBindata(const std::vector<uint8_t>& data, Document* const doc, const char* name)
	{
		doc->bindata[name].clear();
		doc->bindata[name].reserve(data.size());
		std::copy(data.begin(), data.end(), std::back_inserter(doc->bindata[name]));
		return doc->bindata[name].size();
	}

	size_t addBindata(const std::vector<uint8_t>& data, Document* const doc, const char* name)
	{
		doc->bindata[name].reserve(doc->bindata[name].size() + data.size());
		std::copy(data.begin(), data.end(), std::back_inserter(doc->bindata[name]));
		return doc->bindata[name].size();
	}


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
