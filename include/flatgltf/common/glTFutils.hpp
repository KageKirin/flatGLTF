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

	bool				 isDataUri(const char* uri);
	bool				 isDataUri(const std::string& uri);
	std::string			 getUriMimeType(const char* uri);
	std::string			 getUriMimeType(const std::string& uri);
	std::string			 getUriBase64(const char* uri);
	std::string			 getUriBase64(const std::string& uri);
	std::vector<uint8_t> convertUriToData(const char* uri);
	std::vector<uint8_t> convertUriToData(const std::string& uri);
	std::string			 convertDataToUri(const uint8_t* const, size_t, const char* mimeType = nullptr);
	std::string			 convertDataToUri(const std::vector<uint8_t>&, const char* mimeType = nullptr);

	std::vector<uint8_t> decodeBase64(const char* b64sz);
	std::vector<uint8_t> decodeBase64(const std::string& b64sz);
	std::string			 encodeBase64(const uint8_t* const, size_t);
	std::string			 encodeBase64(const std::vector<uint8_t>&);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_common

#endif	// ! FLATGLTF_COMMON_UTILS_H_INC
