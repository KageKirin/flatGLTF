#include "flatgltf/2.0/glTFio.hpp"
#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
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


	///------------------------------------------------------------------------
	/// JSON serialization/deserialization
	///------------------------------------------------------------------------

	static const flatbuffers::IDLOptions& getIDLOptions()
	{
		static flatbuffers::IDLOptions opts;

		opts.strict_json = true;
		return opts;
	};

	std::string to_json(const RootT* const instance)
	{
		// KHUTILS_ASSERT_PTR(instance);

		flatbuffers::Parser parser(getIDLOptions());
		bool				parseOk = parser.Parse(flatgltf_2_0_schema.c_str(), nullptr, "glTF_2.0.fbs");
		KHUTILS_ASSERT_MSG(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return parser.error_;
		}

		std::string jsongen;
		auto		root = CreateRoot(parser.builder_, instance);
		FinishRootBuffer(parser.builder_, root);
		GenerateText(parser, parser.builder_.GetBufferPointer(), &jsongen);
		return jsongen;
	}

	std::string to_json(const Root_t& instance)
	{
		// KHUTILS_ASSERT_PTR(instance);
		return to_json(instance.get());
	}

	//---

	RootT* const from_json(const std::string& json)
	{
		puts(json.c_str());

		flatbuffers::Parser parser;
		bool				parseOk = parser.Parse(flatgltf_2_0_schema.c_str(), nullptr, "glTF_2.0.fbs");
		KHUTILS_ASSERT_MSG(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return nullptr;
		}

		parseOk = parseOk && parser.Parse(json.c_str());
		KHUTILS_ASSERT_MSG(parseOk, parser.error_.c_str());
		if (!parseOk)
		{
			return nullptr;
		}

		auto root = flatbuffers::GetRoot<Root>(parser.builder_.GetBufferPointer());
		return root->UnPack();
	}

	Root_t from_json_internal(const std::string& json)
	{
		return Root_t{from_json(json)};
	}

	///------------------------------------------------------------------------
	/// flatbuffer marshalling/unmarshalling
	///------------------------------------------------------------------------

	std::vector<uint8_t> to_flatbuffer(const RootT* const instance)
	{
		// KHUTILS_ASSERT_PTR(instance);

		flatbuffers::FlatBufferBuilder builder_;
		auto						   root = CreateRoot(builder_, instance);
		FinishRootBuffer(builder_, root);
		return std::vector<uint8_t>{builder_.GetBufferPointer(), builder_.GetBufferPointer() + builder_.GetSize()};
	}

	std::vector<uint8_t> to_flatbuffer(const Root_t& instance)
	{
		// KHUTILS_ASSERT_PTR(instance);
		return to_flatbuffer(instance.get());
	}

	//---

	RootT* const from_flatbuffer(const std::vector<uint8_t>& buffer)
	{
		auto root = flatbuffers::GetRoot<Root>(buffer.data());
		return root->UnPack();
	}

	Root_t from_flatbuffer_internal(const std::vector<uint8_t>& buffer)
	{
		return Root_t{from_flatbuffer(buffer)};
	}


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	namespace fs = boost::filesystem;

	bool loadDocument(Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto p = fs::path(uri);
		if (p.extension() == ".glb")
		{
			return loadDocument_glb_plus(doc, uri);
		}

		if (p.extension() == ".glf")
		{
			return loadDocument_glf_plus(doc, uri);
		}

		if (p.extension() == ".gltf")
		{
			return loadDocument_json_plus(doc, uri);
		}

		return false;
	}

	bool saveDocument(const Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto p = fs::path(uri);
		if (p.extension() == ".glb")
		{
			return saveDocument_glb_plus(doc, uri);
		}

		if (p.extension() == ".glf")
		{
			return saveDocument_glf_plus(doc, uri);
		}

		if (p.extension() == ".gltf")
		{
			return saveDocument_json_plus(doc, uri);
		}


		return false;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------


	// load document as-is, without modification or external data
	bool loadDocument_json(Document* const doc, const char* location, data_reader_t reader)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(reader);

		std::vector<uint8_t> buffer;
		auto				 readOk = reader(location, buffer);

		if (readOk)
		{
			KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);
			std::string jsonString(reinterpret_cast<const char*>(buffer.data()), buffer.size());

			auto newRoot = from_json_internal(jsonString);
			doc->root.swap(newRoot);
			doc->bindata.clear();
			doc->imgdata.clear();
			return true;
		}

		return false;
	}


	bool loadDocument_glf(Document* const doc, const char* location, data_reader_t reader)
	{
		std::vector<uint8_t> buffer;
		auto				 readOk = reader(location, buffer);

		if (readOk)
		{
			KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);
			auto newRoot = from_flatbuffer_internal(buffer);
			doc->root.swap(newRoot);
			doc->bindata.clear();
			doc->imgdata.clear();
			return true;
		}

		return false;
	}

	//-------------------------------------------------------------------------

	// load document: transform data uris to buffers, load external resources
	bool loadDocument_json_plus(Document* const doc, const char* location, data_reader_t reader)
	{
		auto loadOk = loadDocument_json(doc, location, reader);
		if (loadOk)
		{
			for (auto& buf : doc->root->buffers)
			{
				if (isDataUri(buf->uri))
				{
					setBufferData(convertUriToData(buf->uri), doc, buf.get());
				}
				else
				{
					std::vector<uint8_t> bufData;
					auto				 readOk = reader(buf->uri.c_str(), bufData);
					if (readOk)
					{
						setBufferData(bufData, doc, buf.get());
					}
					else
						return false;
				}
			}

			for (auto& img : doc->root->images)
			{
				if (isValidBufferViewId(doc, img->bufferView))
				{
					continue;
				}

				if (isDataUri(img->uri))
				{
					setImageData(convertUriToData(img->uri), doc, img.get());
				}
				else
				{
					std::vector<uint8_t> bufData;
					auto				 readOk = reader(img->uri.c_str(), bufData);
					if (readOk)
					{
						setImageData(bufData, doc, img.get());
					}
					else
					{
						return false;
					}
				}
			}
			return true;
		}

		return false;
	}

	//---

	bool loadDocument_glf_plus(Document* const doc, const char* location, data_reader_t reader)
	{
		auto loadOk = loadDocument_glf(doc, location, reader);
		if (loadOk)
		{
			for (auto& buf : doc->root->buffers)
			{
				if (isDataUri(buf->uri))
				{
					setBufferData(convertUriToData(buf->uri), doc, buf.get());
				}
				else
				{
					std::vector<uint8_t> bufData;
					auto				 readOk = reader(buf->uri.c_str(), bufData);
					if (readOk)
					{
						setBufferData(bufData, doc, buf.get());
					}
					else
						return false;
				}
			}

			for (auto& img : doc->root->images)
			{
				if (isValidBufferViewId(doc, img->bufferView))
				{
					continue;
				}

				if (isDataUri(img->uri))
				{
					setImageData(convertUriToData(img->uri), doc, img.get());
				}
				else
				{
					std::vector<uint8_t> bufData;
					auto				 readOk = reader(img->uri.c_str(), bufData);
					if (readOk)
					{
						setImageData(bufData, doc, img.get());
					}
					else
					{
						return false;
					}
				}
			}
			return true;
		}

		return false;
	}

	//-------------------------------------------------------------------------

	// write document as-is, without modification or external data
	bool saveDocument_json(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(writer);

		auto jsonString = to_json(doc->root);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(jsonString);

		std::vector<uint8_t> buffer;
		buffer.reserve(jsonString.size());
		std::transform(jsonString.begin(), jsonString.end(), std::back_inserter(buffer), [](auto& c) {
			return static_cast<uint8_t>(c);
		});

		return writer(location, buffer);
	}

	//---

	bool saveDocument_glf(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(writer);

		auto buffer = to_flatbuffer(doc->root);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);

		return writer(location, buffer);
	}

	//-------------------------------------------------------------------------
	// write document as-is, write buffers and images set to external URIs

	bool saveDocument_json_plus(const Document* const doc, const char* location, data_writer_t writer)
	{
		auto saveOk = saveDocument_json(doc, location, writer);
		if (saveOk)
		{
			for (auto& buf : doc->root->buffers)
			{
				if (!isDataUri(buf->uri))
				{
					writer(buf->uri.c_str(), getBufferData(doc, buf.get()));
				}
			}

			for (auto& img : doc->root->images)
			{
				if (!isDataUri(img->uri) && !isValidBufferViewId(doc, img->bufferView))
				{
					writer(img->uri.c_str(), getImageData(doc, img.get()));
				}
			}

			return true;
		}

		return false;
	}

	//---

	bool saveDocument_glf_plus(const Document* const doc, const char* location, data_writer_t writer)
	{
		auto saveOk = saveDocument_glf(doc, location, writer);
		if (saveOk)
		{
			for (auto& buf : doc->root->buffers)
			{
				if (!isDataUri(buf->uri))
				{
					writer(buf->uri.c_str(), getBufferData(doc, buf.get()));
				}
			}

			for (auto& img : doc->root->images)
			{
				if (!isDataUri(img->uri) && !isValidBufferViewId(doc, img->bufferView))
				{
					writer(img->uri.c_str(), getImageData(doc, img.get()));
				}
			}

			return true;
		}

		return false;
	}

	//---


	//-------------------------------------------------------------------------

	// write document: ALL buffers/images will be embedded base64 URIs
	bool saveDocument_json_embed(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(writer);

		auto embeddedRoot = embedDocumentBuffersAndImages(doc);
		KHUTILS_ASSERT_PTR(embeddedRoot);

		auto jsonString = to_json(embeddedRoot);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(jsonString);

		std::vector<uint8_t> buffer;
		buffer.reserve(jsonString.size());
		std::transform(jsonString.begin(), jsonString.end(), std::back_inserter(buffer), [](auto& c) {
			return static_cast<uint8_t>(c);
		});

		return writer(location, buffer);
	}

	//---

	bool saveDocument_glf_embed(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(writer);

		auto embeddedRoot = embedDocumentBuffersAndImages(doc);
		KHUTILS_ASSERT_PTR(embeddedRoot);

		auto buffer = to_flatbuffer(embeddedRoot);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);

		return writer(location, buffer);
	}

	//-------------------------------------------------------------------------

	// write document: ALL buffers/images will be external files named after URI or name or counter
	bool saveDocument_json_external(const Document* const _doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocument("copy");

		auto copyOk = cloneDocument(_doc, doc);
		if (copyOk)
		{
			auto disOk = dislodgeDocument(doc);
			if (disOk)
			{
				return saveDocument_json_plus(doc, location, writer);
			}
		}

		return false;
	}

	//---

	bool saveDocument_glf_external(const Document* const _doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocument("copy");

		auto copyOk = cloneDocument(_doc, doc);
		if (copyOk)
		{
			auto disOk = dislodgeDocument(doc);
			if (disOk)
			{
				return saveDocument_glf_plus(doc, location, writer);
			}
		}

		return false;
	}

	//-------------------------------------------------------------------------

	std::vector<uint8_t> createGLBBuffer(const Root_t& root, const std::vector<uint8_t>& _bindata)
	{
		KHUTILS_ASSERT_PTR(root);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(_bindata);

		std::vector<uint8_t> bindata = _bindata;

		auto jsonString = to_json(root);
		jsonString.resize(jsonString.size() + jsonString.size() % 4, 0x20);	// pad to alignment with spaces
		bindata.resize(bindata.size() + bindata.size() % 4, 0x0);			   // pad to alignment with 0

		std::vector<uint8_t> wbuffer;
		wbuffer.reserve(sizeof(GLBHeader) + 2 * sizeof(GLBChunkHeader) + jsonString.size() + bindata.size());

		GLBHeader header;
		KHUTILS_ASSERT_EQUALS(header.magic, (uint32_t)GLBConstant::magic);
		KHUTILS_ASSERT_EQUALS(header.version, (uint32_t)GLBConstant::version);
		header.length = wbuffer.size();

		GLBChunkHeader jsChunk{(uint32_t)jsonString.size(), (uint32_t)GLBConstant::json};
		GLBChunkHeader binChunk{(uint32_t)bindata.size(), (uint32_t)GLBConstant::binary};

		auto bi = std::back_inserter(wbuffer);
		std::copy_n(reinterpret_cast<const uint8_t*>(&header), sizeof(GLBHeader), bi);
		std::copy_n(reinterpret_cast<const uint8_t*>(&jsChunk), sizeof(GLBChunkHeader), bi);
		std::transform(jsonString.begin(), jsonString.end(), bi, [](auto& c) { return static_cast<uint8_t>(c); });
		std::copy_n(reinterpret_cast<const uint8_t*>(&binChunk), sizeof(GLBChunkHeader), bi);
		std::copy(bindata.begin(), bindata.end(), bi);

		KHUTILS_ASSERT_CNTR_NOT_EMPTY(wbuffer);
		return wbuffer;
	}

	//-------------------------------------------------------------------------

	// write document to glTF-binary: all buffers merged into 1, external or data uris as-is
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

	// write document to glTF-binary: all buffers merged into 1, external or data uris as-is
	bool saveDocument_glb_plus(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		Root_t				 root;
		std::vector<uint8_t> bindata;
		std::tie(root, bindata) = binarizeDocumentBuffers(doc, false);

		auto wbuffer = createGLBBuffer(root, bindata);
		auto writeOk = writer(location, wbuffer);

		if (writeOk)
		{
			for (auto& img : doc->root->images)
			{
				if (!isDataUri(img->uri) && !isValidBufferViewId(doc, img->bufferView))
				{
					writer(img->uri.c_str(), getImageData(doc, img.get()));
				}
			}
			return true;
		}

		return false;
	}

	//---

	// write document to glTF-binary: all buffers merged into 1, ALL external images will be embedded base64 URIs
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

	// write document to glTF-binary: all buffers merged into 1, ALL external images also transformed to use bufferView
	bool saveDocument_glb_buffer(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		Root_t				 root;
		std::vector<uint8_t> bindata;
		std::tie(root, bindata) = binarizeDocumentBuffers(doc, true);

		auto wbuffer = createGLBBuffer(root, bindata);
		return writer(location, wbuffer);
	}

	//---

	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
