#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/2.0/glTFio.hpp"
#include "flatgltf/common/glTFutils.hpp"
#include "glTFinternal.hpp"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"

#define KHUTILS_ASSERTION_INLINE
#include "khutils/assertion.hpp"
#include "khutils/file.hpp"
#include "khutils/logging.hpp"
#include "khutils/runtime_exceptions.hpp"

/// terribly sorry for this dependency. will remove asap
#include <boost/filesystem/path.hpp>


#include <algorithm>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

// flatbuffer schema string for parser
extern const std::string flatgltf_2_0_schema;


namespace glTF_2_0
{
	using namespace glTF_common;

	///------------------------------------------------------------------------
	/// types for GLB files
	///------------------------------------------------------------------------

	MANUALLY_ALIGNED_STRUCT(4) GLBHeader
	{
		/// magic equals 0x46546C67. It is ASCII string 'glTF', and can be used to identify data as Binary glTF.
		uint32_t magic = (uint32_t)GLBConstant::magic;

		/// version indicates the version of the Binary glTF container format. This specification defines version 2.
		uint32_t version = (uint32_t)GLBConstant::version;

		/// length is the total length of the Binary glTF, including Header and all Chunks, in bytes.
		uint32_t length;
	};
	static_assert(sizeof(GLBHeader) == 12, "GLBHeader is not 12 bytes");


	MANUALLY_ALIGNED_STRUCT(4) GLBChunkHeader
	{
		/// chunkLength is the length of chunkData, in bytes.
		/// NOTE: must be modulo 4
		uint32_t chunkLength;

		/// chunkType indicates the type of chunk. See Table 1 for details.
		/// chunkType equals 0x4E4F534A, ASCII string 'JSON' -> GLBConstant::json
		/// chunkType equals 0x004E4942	, ASCII string 'BIN' -> GLBConstant::binary
		uint32_t chunkType;
	};
	static_assert(sizeof(GLBChunkHeader) == 8, "GLBChunkHeader is not 8 bytes");

	//-------------------------------------------------------------------------

	///------------------------------------------------------------------------
	/// helper function to create GLB file buffer
	///------------------------------------------------------------------------

	std::vector<uint8_t> createGLBBuffer(const Root_t& root, const std::vector<uint8_t>& bindata)
	{
		KHUTILS_ASSERT_PTR(root);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(bindata);

		auto jsonString = to_json(root);
		jsonString.resize(jsonString.size() + jsonString.size() % 4, 0x20);	// pad to alignment with spaces

		auto jsonStringSize = jsonString.size();
		auto bindataSize	= bindata.size() + bindata.size() % 4;

		std::vector<uint8_t> wbuffer;
		wbuffer.reserve(sizeof(GLBHeader) + 2 * sizeof(GLBChunkHeader) + jsonStringSize + bindataSize);

		GLBHeader header;
		KHUTILS_ASSERT_EQUALS(header.magic, (uint32_t)GLBConstant::magic);
		KHUTILS_ASSERT_EQUALS(header.version, (uint32_t)GLBConstant::version);
		header.length = wbuffer.size();

		GLBChunkHeader jsChunk{(uint32_t)jsonStringSize, (uint32_t)GLBConstant::json};
		GLBChunkHeader binChunk{(uint32_t)bindataSize, (uint32_t)GLBConstant::binary};

		auto bi = std::back_inserter(wbuffer);
		std::copy_n(reinterpret_cast<const uint8_t*>(&header), sizeof(GLBHeader), bi);
		std::copy_n(reinterpret_cast<const uint8_t*>(&jsChunk), sizeof(GLBChunkHeader), bi);
		std::transform(jsonString.begin(), jsonString.end(), bi, [](auto& c) { return static_cast<uint8_t>(c); });
		std::copy_n(reinterpret_cast<const uint8_t*>(&binChunk), sizeof(GLBChunkHeader), bi);
		std::copy(bindata.begin(), bindata.end(), bi);
		wbuffer.resize(wbuffer.size() + wbuffer.size() % 4, 0x0);	// pad to alignment with 0

		KHUTILS_ASSERT_CNTR_NOT_EMPTY(wbuffer);
		return wbuffer;
	}

	//---

	bool readGLBBuffer(Document* const doc, const std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);
		if (buffer.empty())
		{
			return false;
		}

		const GLBHeader& header = *reinterpret_cast<const GLBHeader*>(&*buffer.begin());
		KHUTILS_ASSERT_EQUALS(header.magic, (uint32_t)GLBConstant::magic);
		KHUTILS_ASSERT_EQUALS(header.version, (uint32_t)GLBConstant::version);
		KHUTILS_ASSERT_EQUALS(header.length, (uint32_t)buffer.size());

		const GLBChunkHeader& jsChunk = *reinterpret_cast<const GLBChunkHeader*>(&*(buffer.begin() + sizeof(GLBHeader)));
		assert(jsChunk.chunkType == (uint32_t)GLBConstant::json);
		assert(jsChunk.chunkLength >= sizeof(GLBChunkHeader));
		assert((jsChunk.chunkLength % 4) == 0);

		std::string jsonString(reinterpret_cast<const char*>(&*(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader))));
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(jsonString);

		doc->root = from_json_internal(jsonString);

		// check if there's more data, i.e. binary chunk
		if (header.length > sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength)
		{
			const GLBChunkHeader& binChunk = *reinterpret_cast<const GLBChunkHeader*>(
			  &*(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength));
			assert(binChunk.chunkType == (uint32_t)GLBConstant::binary);
			assert(binChunk.chunkLength >= sizeof(GLBChunkHeader));
			assert((binChunk.chunkLength % 4) == 0);

			auto buf = getBuffer(doc, 0);
			KHUTILS_ASSERT_PTR(buf);
			KHUTILS_ASSERT(!isDataUri(buf->uri));

			auto bindata = std::vector<uint8_t>{buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader)
												  + jsChunk.chunkLength + sizeof(GLBChunkHeader),
												buffer.end()};
			auto bufSize = setBufferData(bindata, doc, buf);
			return bufSize == bindata.size();
		}

		return true;
	}


	//-------------------------------------------------------------------------

	///------------------------------------------------------------------------
	/// load document from glTF-binary: all buffers merged into 1, without external data
	///------------------------------------------------------------------------

	bool loadDocument_glb(Document* const doc, const char* location, data_reader_t reader)
	{
		KHUTILS_ASSERT_PTR(doc);

		std::vector<uint8_t> buffer;
		return reader(location, buffer) && readGLBBuffer(doc, buffer);
	}

	//---

	///------------------------------------------------------------------------
	/// write document to glTF-binary: all buffers merged into 1, external or data uris as-is
	///------------------------------------------------------------------------

	bool saveDocument_glb(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		Root_t				 root;
		std::vector<uint8_t> bindata;
		std::tie(root, bindata) = binarizeDocumentBuffers(doc, false);

		auto wbuffer = createGLBBuffer(root, bindata);
		return writer(location, wbuffer);
	}

	//---

	///------------------------------------------------------------------------
	/// write document to glTF-binary: all buffers merged into 1, ALL external images will be embedded base64 URIs
	///------------------------------------------------------------------------

	bool saveDocument_glb_embed(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		Root_t				 root;
		std::vector<uint8_t> bindata;
		std::tie(root, bindata) = binarizeDocumentBuffers_embedImages(doc, true);

		auto wbuffer = createGLBBuffer(root, bindata);
		return writer(location, wbuffer);
	}

	//---

	///------------------------------------------------------------------------
	/// write document to glTF-binary: all buffers merged into 1, ALL external images also transformed to use bufferView
	///------------------------------------------------------------------------

	bool saveDocument_glb_buffer(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		Root_t				 root;
		std::vector<uint8_t> bindata;
		std::tie(root, bindata) = binarizeDocumentBuffers(doc, true);

		auto wbuffer = createGLBBuffer(root, bindata);
		return writer(location, wbuffer);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
