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
	/// JSON serialization/deserialization
	///------------------------------------------------------------------------

	static const flatbuffers::IDLOptions& getIDLOptions()
	{
		static flatbuffers::IDLOptions opts;

		opts.strict_json = true;
		return opts;
	}

	//---

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

	//---

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

	//---

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

	//---

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

	//---

	Root_t from_flatbuffer_internal(const std::vector<uint8_t>& buffer)
	{
		return Root_t{from_flatbuffer(buffer)};
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
