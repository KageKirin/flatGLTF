#ifndef FLATGLTF_COMMON_UTILS_H_INC
#define FLATGLTF_COMMON_UTILS_H_INC

#include "../common/glTF_api_exports.h"

#include <cctype>
#include <string>
#include <vector>

namespace glTF_common
{
	///-----------------------------------------------------------------------
	/// Base64 tools
	///-----------------------------------------------------------------------

	bool				 is_DataUri(const char* uri);
	bool				 is_DataUri(const std::string& uri);
	std::string			 get_UriMimeType(const char* uri);
	std::string			 get_UriMimeType(const std::string& uri);
	std::string			 get_UriBase64(const char* uri);
	std::string			 get_UriBase64(const std::string& uri);
	std::vector<uint8_t> convert_UriToData(const char* uri);
	std::vector<uint8_t> convert_UriToData(const std::string& uri);
	std::string			 convert_DataToUri(const uint8_t* const, size_t, const char* mimeType = nullptr);
	std::string			 convert_DataToUri(const std::vector<uint8_t>&, const char* mimeType = nullptr);

	std::vector<uint8_t> decode_Base64(const char* b64sz);
	std::vector<uint8_t> decode_Base64(const std::string& b64sz);
	std::string			 encode_Base64(const uint8_t* const, size_t);
	std::string			 encode_Base64(const std::vector<uint8_t>&);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_common

#endif	// ! FLATGLTF_COMMON_UTILS_H_INC
