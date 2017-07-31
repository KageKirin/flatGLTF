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

	bool loadDocument_json_buffer(Document* const doc, const std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		std::string json(reinterpret_cast<const char*>(buffer.data()), buffer.size() - 1);
		doc->root = from_json_internal(json);
		return true;
	}

	//---

	std::vector<uint8_t> saveDocument_json_buffer(const Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);
		auto json = to_json(doc->root);
		return std::vector<uint8_t>{reinterpret_cast<const uint8_t*>(&*json.begin()),
									reinterpret_cast<const uint8_t*>(&*json.end())};
	}

	//-------------------------------------------------------------------------

	bool loadDocument_glb_buffer(Document* const doc, const std::vector<uint8_t>& buffer)
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
		assert(jsChunk.chunkLength >= 4);
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
			assert(binChunk.chunkLength >= 4);
			assert((binChunk.chunkLength % 4) == 0);

			doc->bindata["binary"].reserve(binChunk.chunkLength);
			std::copy(buffer.begin() + sizeof(GLBHeader) + sizeof(GLBChunkHeader) + jsChunk.chunkLength + sizeof(GLBChunkHeader),
					  buffer.end(),
					  std::back_inserter(doc->bindata["binary"]));
		}

		return true;
	}

	//---

	std::vector<uint8_t> saveDocument_glb_buffer(const Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);
		auto jsonString = to_json(doc->root);
		jsonString.resize(jsonString.size() + jsonString.size() % 4, 0x20);	// pad to alignment with spaces

		size_t bindataSize = std::accumulate(doc->bindata.begin(), doc->bindata.end(), size_t(0), [](size_t sum, auto& kvp) {
			return sum + kvp.second.size() + kvp.second.size() % 4;	// pad to alignment with 0
		});

		std::vector<uint8_t> buffer;
		buffer.reserve(sizeof(GLBHeader) + 2 * sizeof(GLBChunkHeader) + jsonString.size() + bindataSize);

		GLBHeader header;
		KHUTILS_ASSERT_EQUALS(header.magic, (uint32_t)GLBConstant::magic);
		KHUTILS_ASSERT_EQUALS(header.version, (uint32_t)GLBConstant::version);
		header.length = buffer.size();

		GLBChunkHeader jsChunk{(uint32_t)jsonString.size(), (uint32_t)GLBConstant::json};
		GLBChunkHeader binChunk{(uint32_t)bindataSize, (uint32_t)GLBConstant::binary};

		auto bi = std::back_inserter(buffer);
		std::copy_n(reinterpret_cast<const uint8_t*>(&header), sizeof(GLBHeader), bi);
		std::copy_n(reinterpret_cast<const uint8_t*>(&jsChunk), sizeof(GLBChunkHeader), bi);
		std::transform(jsonString.begin(), jsonString.end(), bi, [](auto& c) { return static_cast<uint8_t>(c); });
		std::copy_n(reinterpret_cast<const uint8_t*>(&binChunk), sizeof(GLBChunkHeader), bi);
		std::for_each(doc->bindata.begin(), doc->bindata.end(), [&bi](auto& kvp) {
			std::copy(kvp.second.begin(), kvp.second.end(), bi);
			std::fill_n(bi, kvp.second.size() % 4, 0x0);	// pad to alignment with 0
		});

		KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);
		return buffer;
	}

	//-------------------------------------------------------------------------

	bool loadDocument_glf_buffer(Document* const doc, const std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		doc->root = from_flatbuffer_internal(buffer);
		return true;
	}

	//---

	std::vector<uint8_t> saveDocument_glf_buffer(const Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);
		return to_flatbuffer(doc->root);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	static bool _load_file(FILE* file, std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(file);
		auto bi = std::back_inserter(buffer);
		while (file && !feof(file))
		{
			*bi++ = fgetc(file);
		}
		return true;
	}

	//---

	static bool _load_uri(const char* uri, std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(uri);
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(uri, "rb"), fclose);
		return _load_file(file.get(), buffer);
	}

	//---

	static bool _load_stream(std::istream& ins, std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT((bool)ins);
		auto bi = std::back_inserter(buffer);
		do
		{
			char c;
			ins.read(&c, 1);
			*bi++ = c;
		} while (ins);
		return true;
	}


	typedef bool (*Document_load_buffer_t)(Document* const, const std::vector<uint8_t>&);

	static bool _load_file(Document* const doc, FILE* file, Document_load_buffer_t loader)
	{
		KHUTILS_ASSERT_PTR(doc);
		std::vector<uint8_t> buffer;
		return _load_file(file, buffer) && loader(doc, buffer);
	}

	//---

	static bool _load_uri(Document* const doc, const char* uri, Document_load_buffer_t loader)
	{
		KHUTILS_ASSERT_PTR(doc);
		std::vector<uint8_t> buffer;
		return _load_uri(uri, buffer) && loader(doc, buffer);
	}

	//---

	static bool _load_stream(Document* const doc, std::istream& ins, Document_load_buffer_t loader)
	{
		KHUTILS_ASSERT_PTR(doc);
		std::vector<uint8_t> buffer;
		return _load_stream(ins, buffer) && loader(doc, buffer);
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool loadDocument_json(Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_uri(doc, uri, &loadDocument_json_buffer);
	}

	//---

	bool loadDocument_json(Document* const doc, FILE* file)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_file(doc, file, loadDocument_json_buffer);
	}

	//---

	bool loadDocument_json(Document* const doc, std::istream& ins)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_stream(doc, ins, loadDocument_json_buffer);
	}

	//---

	bool loadDocument_json(Document* const doc, const std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		return loadDocument_json_buffer(doc, buffer);
	}

	//---
	//---

	bool loadDocument_glb(Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_uri(doc, uri, loadDocument_glb_buffer);
	}

	//---

	bool loadDocument_glb(Document* const doc, FILE* file)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_file(doc, file, loadDocument_glb_buffer);
	}

	//---

	bool loadDocument_glb(Document* const doc, std::istream& ins)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_stream(doc, ins, loadDocument_glb_buffer);
	}

	//---

	bool loadDocument_glb(Document* const doc, const std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		return loadDocument_glb_buffer(doc, buffer);
	}

	//---
	//---

	bool loadDocument_glf(Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_uri(doc, uri, loadDocument_glf_buffer);
	}

	//---

	bool loadDocument_glf(Document* const doc, FILE* file)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_file(doc, file, loadDocument_glf_buffer);
	}

	//---

	bool loadDocument_glf(Document* const doc, std::istream& ins)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _load_stream(doc, ins, loadDocument_glf_buffer);
	}

	//---

	bool loadDocument_glf(Document* const doc, const std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		return loadDocument_glf_buffer(doc, buffer);
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	static bool _save_file(FILE* file, const std::vector<uint8_t>& buffer)
	{
		if (file)
		{
			auto written = fwrite(buffer.data(), buffer.size(), 1, file);
			return written == 1 && ftell(file) == buffer.size();
		}
		return false;
	}

	//---

	static bool _save_uri(const char* uri, const std::vector<uint8_t>& buffer)
	{
		auto file = std::unique_ptr<FILE, decltype(&fclose)>(fopen(uri, "wb"), fclose);
		return _save_file(file.get(), buffer);
	}

	//---

	static bool _save_stream(std::ostream& outs, const std::vector<uint8_t>& buffer)
	{
		if (outs)
		{
			outs.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
			auto written = outs.tellp();
			return written == buffer.size();
		}
		return false;
	}

	//---
	//---

	bool saveDocument_json(const Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_uri(uri, saveDocument_json_buffer(doc));
	}

	//---

	bool saveDocument_json(const Document* const doc, FILE* file)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_file(file, saveDocument_json_buffer(doc));
	}

	//---

	bool saveDocument_json(const Document* const doc, std::ostream& outs)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_stream(outs, saveDocument_json_buffer(doc));
	}

	//---

	bool saveDocument_json(const Document* const doc, std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		buffer = saveDocument_json_buffer(doc);
		return true;
	}

	//---
	//---

	bool saveDocument_glb(const Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_uri(uri, saveDocument_glb_buffer(doc));
	}

	//---

	bool saveDocument_glb(const Document* const doc, FILE* file)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_file(file, saveDocument_glb_buffer(doc));
	}

	//---

	bool saveDocument_glb(const Document* const doc, std::ostream& outs)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_stream(outs, saveDocument_glb_buffer(doc));
	}

	//---

	bool saveDocument_glb(const Document* const doc, std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		buffer = saveDocument_glb_buffer(doc);
		return true;
	}

	//---
	//---

	bool saveDocument_glf(const Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_uri(uri, saveDocument_glf_buffer(doc));
	}

	//---

	bool saveDocument_glf(const Document* const doc, FILE* file)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_file(file, saveDocument_glf_buffer(doc));
	}

	//---

	bool saveDocument_glf(const Document* const doc, std::ostream& outs)
	{
		KHUTILS_ASSERT_PTR(doc);
		return _save_stream(outs, saveDocument_glf_buffer(doc));
	}

	//---

	bool saveDocument_glf(const Document* const doc, std::vector<uint8_t>& buffer)
	{
		KHUTILS_ASSERT_PTR(doc);
		buffer = saveDocument_glf_buffer(doc);
		return true;
	}

	//---
	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	bool loadDocument_bindata(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);

		return std::all_of(doc->root->buffers.begin(), doc->root->buffers.end(), [&](auto& buf) {
			return isDataUri(buf->uri.c_str()) || loadDocument_bindata(createBindata(doc, buf->uri.c_str()), buf->uri.c_str());
		});
	}

	//---

	bool saveDocument_bindata(const Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);

		return std::all_of(doc->bindata.begin(), doc->bindata.end(), [&](auto& bd) {
			return saveDocument_bindata(bd.second, bd.first.c_str());
		});
	}

	//---

	bool loadDocument_bindata(std::vector<uint8_t>& bindata, const char* uri)
	{
		if (isDataUri(uri))
			return true;

		return _load_uri(uri, bindata);
	}

	//---

	bool loadDocument_bindata(std::vector<uint8_t>& bindata, FILE* file)
	{
		return _load_file(file, bindata);
	}

	//---

	bool loadDocument_bindata(std::vector<uint8_t>& bindata, std::istream& ins)
	{
		return _load_stream(ins, bindata);
	}

	//---

	bool saveDocument_bindata(const std::vector<uint8_t>& bindata, const char* uri)
	{
		KHUTILS_ASSERT(!isDataUri(uri));
		return _save_uri(uri, bindata);
	}

	//---

	bool saveDocument_bindata(const std::vector<uint8_t>& bindata, FILE* file)
	{
		return _save_file(file, bindata);
	}

	//---

	bool saveDocument_bindata(const std::vector<uint8_t>& bindata, std::ostream& outs)
	{
		return _save_stream(outs, bindata);
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	namespace fs = boost::filesystem;

	bool loadDocument(Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto p = fs::path(uri);
		if (p.extension() == ".glb")
		{
			return loadDocument_glb(doc, uri);
		}

		if (p.extension() == ".glf")
		{
			return loadDocument_glf(doc, uri);
		}

		if (p.extension() == ".gltf")
		{
			return loadDocument_json(doc, uri) && loadDocument_bindata(doc);
		}

		return false;
	}

	bool saveDocument(const Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto p = fs::path(uri);
		if (p.extension() == ".glb")
		{
			return saveDocument_glb(doc, uri);
		}

		if (p.extension() == ".glf")
		{
			return saveDocument_glf(doc, uri);
		}

		if (p.extension() == ".gltf")
		{
			return saveDocument_json(doc, uri) && saveDocument_bindata(doc);
		}


		return false;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
