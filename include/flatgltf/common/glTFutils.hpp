#ifndef FLATGLTF_COMMON_UTILS_H_INC
#define FLATGLTF_COMMON_UTILS_H_INC

#include "flatgltf/common/glTFapiexports.h"

#include <cctype>
#include <string>
#include <vector>

namespace glTF_common
{
	///-----------------------------------------------------------------------
	/// Base64 tools
	///-----------------------------------------------------------------------

	// returns true if uri is data uri ('data:')
	bool isDataUri(const char* uri);
	bool isDataUri(const std::string& uri);

	// get mime type from data uri
	// returns empty string if not set
	std::string getUriMimeType(const char* uri);
	std::string getUriMimeType(const std::string& uri);

	// get base64 part from data uri
	// returns empty string if not set
	std::string getUriBase64(const char* uri);
	std::string getUriBase64(const std::string& uri);

	// set base64 part of data uri
	// returns complete string
	std::string setUriBase64(const char* uri, const char* base64);
	std::string setUriBase64(const std::string& uri, const std::string& base64);

	// converts data uri to contained data
	std::vector<uint8_t> convertUriToData(const char* uri);
	std::vector<uint8_t> convertUriToData(const std::string& uri);

	// converts data to data uri following optional mimetype
	// returns complete data uri string
	std::string convertDataToUri(const uint8_t* const, size_t, const char* mimeType = nullptr);
	std::string convertDataToUri(const std::vector<uint8_t>&, const char* mimeType = nullptr);

	// converts base64 string to contained data
	// NOTE: only base64 string, NOT data uri
	std::vector<uint8_t> decodeBase64(const char* b64sz);
	std::vector<uint8_t> decodeBase64(const std::string& b64sz);

	// converts data to base64 string
	// NOTE: only base64 string, NOT data uri
	std::string encodeBase64(const uint8_t* const, size_t);
	std::string encodeBase64(const std::vector<uint8_t>&);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

	bool writeData(const char* location, const std::vector<uint8_t>&);
	bool readData(const char* location, std::vector<uint8_t>&);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_common

#endif	// ! FLATGLTF_COMMON_UTILS_H_INC
