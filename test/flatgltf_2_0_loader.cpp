//! test fot flatgltf / glTF 2.0 loading

#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"
#include "flatbuffers/util.h"

#include "catch.hpp"

#include <iostream>
#include <sstream>
#include <string>

extern const std::string flatgltf_2_0_schema;

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
		auto doc
		  = std::unique_ptr<glTF_2_0::glTF_Document, decltype(&glTF_2_0::destroy_Document)>(glTF_2_0::create_Document("test"),
																							&glTF_2_0::destroy_Document);

		std::cout << "----------------------" << std::endl;
		auto iss	= std::istringstream(gltfFileContents);
		bool loadOk = glTF_2_0::load_Document(doc.get(), iss);
		if (!loadOk)
		{
			std::cerr << "loading failed" << std::endl;
		}

		std::cout << "----------------------" << std::endl;
		auto oss	= std::ostringstream();
		bool saveOk = glTF_2_0::save_Document(doc.get(), oss);
		std::cout << oss.str() << std::endl;
		if (!saveOk)
		{
			std::cerr << "saving failed" << std::endl;
		}
	}


	return 0;
}
