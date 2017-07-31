#ifndef FLATGLTF_2_0_IO_API_H_INC
#define FLATGLTF_2_0_IO_API_H_INC

#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFmath_types.hpp"
#include "flatgltf/common/glTFapiexports.h"

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

	// document file interface
	//! saves/loads document + bindata attachments
	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument(Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument(const Document* const, const char* uri);

	// JSON file interface
	//! saves/loads document JSON part
	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_json(Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_json(const Document* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_json(Document* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_json(const Document* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_json(Document* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_json(const Document* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_json(Document* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_json(const Document* const, std::vector<uint8_t>& buffer);

	// API to fill/dump bindata from glTF
	// file interface for external bindata resources
	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_bindata(Document*);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_bindata(const Document*);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_bindata(std::vector<uint8_t>& bindata, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_bindata(const std::vector<uint8_t>& bindata, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_bindata(std::vector<uint8_t>& bindata, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_bindata(const std::vector<uint8_t>& bindata, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_bindata(std::vector<uint8_t>& buffer, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_bindata(const std::vector<uint8_t>& buffer, std::ostream&);

	// GLB file interface
	//! saves/loads GLB data
	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glb(Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glb(const Document* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glb(Document* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glb(const Document* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glb(Document* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glb(const Document* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glb(Document* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glb(const Document* const, std::vector<uint8_t>& buffer);

	// GLF file interface
	//! GLF is a FlatGLTF original format, basically JSON dumped as flatbuffer
	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glf(Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glf(const Document* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glf(Document* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glf(const Document* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glf(Document* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glf(const Document* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API loadDocument_glf(Document* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API saveDocument_glf(const Document* const, std::vector<uint8_t>& buffer);

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
