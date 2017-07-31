#ifndef FLATGLTF_2_0_IO_API_H_INC
#define FLATGLTF_2_0_IO_API_H_INC

#include "../common/glTF_api_exports.h"
#include "glTF_generated.h"
#include "glTF_types.h"
#include "glb.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

namespace glTF_2_0
{
	//! marshal glTF object to JSON
	std::string to_json(const Root_t&);
	//! unmarshal glTF object form JSON
	Root_t from_json(const std::string&);

	//! flatbuffer-serialize glTF object to buffer
	std::vector<uint8_t> to_flatbuffer(const Root_t&);
	//! flatbuffer-deserialize glTF object from buffer
	Root_t from_flatbuffer(const std::vector<uint8_t>&);


	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_IO_API_H_INC
