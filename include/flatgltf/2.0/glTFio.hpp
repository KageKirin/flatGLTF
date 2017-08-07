#ifndef FLATGLTF_2_0_IO_API_H_INC
#define FLATGLTF_2_0_IO_API_H_INC

#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/2.0/glTFmath_types.hpp"
#include "flatgltf/common/glTFapiexports.h"
#include "flatgltf/common/glTFutils.hpp"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>

namespace glTF_2_0
{
	///-----------------------------------------------------------------------
	/// utility
	///-----------------------------------------------------------------------

	/// clone a document into a new one
	FLATGLTF_DLL_FUNC bool FLATGLTF_API cloneDocument(const Document* const source, Document* const target);

	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API binarizeDocument(Document* const);

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API embedDocument(Document* const);

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API dislodgeDocument(Document* const);

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API splitDocument(Document* const);

	///-----------------------------------------------------------------------
	/// file I/O
	///-----------------------------------------------------------------------

	bool loadDocument(Document* const, const char* location);
	bool saveDocument(const Document* const, const char* location);

	// requried IO funcs
	// - read/write JSON (only)
	// - read/write JSON + external
	// - read/write GLF (only)
	// - read/write GLF + external
	// - read/write GLB (only)
	// - read/write GLB + external (images)

	typedef bool (*data_writer_t)(const char* location, const std::vector<uint8_t>&);
	typedef bool (*data_reader_t)(const char* location, std::vector<uint8_t>&);

	// load document as-is, without modification or external data
	bool loadDocument_json(Document* const, const char* location, data_reader_t = &glTF_common::readData);
	bool loadDocument_glf(Document* const, const char* location, data_reader_t = &glTF_common::readData);

	// load document: transform data uris to buffers, load external resources
	bool loadDocument_json_plus(Document* const, const char* location, data_reader_t = &glTF_common::readData);
	bool loadDocument_glf_plus(Document* const, const char* location, data_reader_t = &glTF_common::readData);


	// write document as-is, without modification or external data
	bool saveDocument_json(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);
	bool saveDocument_glf(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);

	// write document as-is, write buffers and images set to external URIs
	bool saveDocument_json_plus(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);
	bool saveDocument_glf_plus(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);

	// write document: ALL buffers/images will be embedded base64 URIs
	bool saveDocument_json_embed(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);
	bool saveDocument_glf_embed(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);

	// write document: ALL buffers/images will be external files named after URI or name or counter
	bool saveDocument_json_external(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);
	bool saveDocument_glf_external(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);


	// write document to glTF-binary: all buffers merged into 1, without external data
	bool saveDocument_glb(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);

	// write document to glTF-binary: all buffers merged into 1, ALL external images will be embedded base64 URIs
	bool saveDocument_glb_embed(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);

	// write document to glTF-binary: all buffers merged into 1, ALL external images also transformed to use bufferView
	bool saveDocument_glb_buffer(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);

	// write document to glTF-binary: all buffers merged into 1, with external data
	bool saveDocument_glb_plus(const Document* const, const char* location, data_writer_t = &glTF_common::writeData);


	// load document from glTF-binary: all buffers merged into 1, without external data
	bool loadDocument_glb(Document* const, const char* location, data_reader_t = &glTF_common::readData);

	// load document from glTF-binary: all buffers merged into 1, with external data
	bool loadDocument_glb_plus(Document* const, const char* location, data_reader_t = &glTF_common::readData);

	///-----------------------------------------------------------------------

	//! marshal glTF object to JSON
	FLATGLTF_DLL_FUNC std::string FLATGLTF_API to_json(const RootT* const);
	//! unmarshal glTF object form JSON
	FLATGLTF_DLL_FUNC RootT* const FLATGLTF_API from_json(const std::string&);

	//! flatbuffer-serialize glTF object to buffer
	FLATGLTF_DLL_FUNC std::vector<uint8_t> FLATGLTF_API to_flatbuffer(const RootT* const);
	//! flatbuffer-deserialize glTF object from buffer
	FLATGLTF_DLL_FUNC RootT* const FLATGLTF_API from_flatbuffer(const std::vector<uint8_t>&);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_IO_API_H_INC
