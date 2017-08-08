//! test fot flatgltf / glTF 2.0 loading

#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/2.0/glTFio.hpp"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#define KHUTILS_FILE_IMPL
#define KHUTILS_LOGGING_IMPL
#define KHUTILS_ASSERTION_INLINE
#define KHUTILS_ASSERTION_IMPL
#define KHUTILS_RUNTIME_EXCEPTIONS_IMPL
#include "khutils/assertion.hpp"
#include "khutils/file.hpp"
#include "khutils/logging.hpp"
#include "khutils/runtime_exceptions.hpp"

#include <iostream>
#include <sstream>
#include <string>

extern const std::string flatgltf_2_0_schema;
using namespace glTF_2_0;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << argv[0] << " <file>.gltf" << std::endl;
		return -1;
	}

	std::string gltfFileContents;
	bool		gotFile = flatbuffers::LoadFile(argv[1], false, &gltfFileContents);

	if (!gotFile)
	{
		std::cerr << argv[1] << " does not seem to exist" << std::endl;
		return -1;
	}


	flatbuffers::Parser parser;
	bool				schemaOk = parser.Parse(flatgltf_2_0_schema.c_str(), nullptr, "glTF.fbs");
	if (!schemaOk)
	{
		std::cerr << "schema error: " << parser.error_ << std::endl;
		return 1;
	}

	bool gltfOk = parser.Parse(gltfFileContents.c_str(), nullptr, argv[1]);
	if (!gltfOk)
	{
		std::cerr << "json error: " << parser.error_ << std::endl;
		return 2;
	}

	std::cout << "gltf json file could be loaded" << std::endl;
	std::cout << gltfFileContents << std::endl;
	{
		auto doc = std::unique_ptr<Document, decltype(&destroyDocument)>(createDocument("test"), &destroyDocument);
		std::cout << "----------------------" << std::endl;
		auto iss	= std::istringstream(gltfFileContents);
		bool loadOk = loadDocument_json(doc.get(),
										"",	//
										[&](const char*, std::vector<uint8_t>& data) {
											data= khutils::openBufferFromStream(iss);
											return true;
										});
		if (!loadOk)
		{
			std::cerr << "loading failed" << std::endl;
		}

		std::cout << "----------------------" << std::endl;
		auto oss	= std::ostringstream();
		bool saveOk = saveDocument_json(doc.get(),
										"",	//
										[&](const char*, const std::vector<uint8_t>& data) {
											khutils::dumpBufferToStream(data, oss);
											return true;
										});
		std::cout << oss.str() << std::endl;
		if (!saveOk)
		{
			std::cerr << "saving failed" << std::endl;
		}
	}


	return 0;
}
