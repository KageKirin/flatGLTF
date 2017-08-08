#include "flatgltf/common/glTFutils.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"


#include <cctype>
#include <regex>
#include <string>
#include <vector>

namespace glTF_common
{
	///-----------------------------------------------------------------------
	/// Base64 tools
	///-----------------------------------------------------------------------

	static constexpr char reDataUri[] = R"(/^data:(.*?)(;base64)?,(.*)$/;)";

	bool isDataUri(const char* uri)
	{
		return std::regex_match(uri, std::regex(reDataUri));
	}

	bool isDataUri(const std::string& uri)
	{
		return isDataUri(uri.c_str());
	}

	//---

	inline std::string getUriPart(const char* uri, size_t part)
	{
		std::cmatch matches;
		if (std::regex_match(uri, matches, std::regex(reDataUri)))
		{
			if (part < matches.size())
			{
				return matches.str(part);
			}
		}
		return std::string();
	}

	// get mime type from data uri
	// returns empty string if not set
	std::string getMimeType(const char* uri)
	{
		return getUriPart(uri, 1);
	}

	std::string getMimeType(const std::string& uri)
	{
		return getMimeType(uri.c_str());
	}

	// get base64 part from data uri
	// returns empty string if not set
	std::string getUriBase64(const char* uri)
	{
		return getUriPart(uri, 2);
	}

	std::string getUriBase64(const std::string& uri)
	{
		return getUriBase64(uri.c_str());
	}

	//---

	// set base64 part of data uri
	// returns complete string
	std::string setUriBase64(const char* uri, const char* base64)
	{
		return std::string(uri) + "," + base64;
	}

	std::string setUriBase64(const std::string& uri, const std::string& base64)
	{
		return setUriBase64(uri.c_str(), base64.c_str());
	}

	//---

	// converts data uri to contained data
	std::vector<uint8_t> convertUriToData(const char* uri)
	{
		return decodeBase64(getUriBase64(uri));
	}

	std::vector<uint8_t> convertUriToData(const std::string& uri)
	{
		return convertUriToData(uri.c_str());
	}

	//---

	// converts data to data uri following optional mimetype
	// returns complete data uri string
	std::string convertDataToUri(const uint8_t* const data, size_t length, const char* mimeType)
	{
		// data:application/octet-stream;base64,<data>
		return std::string("data:") + mimeType + ";base64," + encodeBase64(data, length);
	}

	std::string convertDataToUri(const std::vector<uint8_t>& data, const char* mimeType)
	{
		return convertDataToUri(data.data(), data.size(), mimeType);
	}


	//---
	static const std::string base64Characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	// converts base64 string to contained data
	// NOTE: only base64 string, NOT data uri

	std::vector<uint8_t> decodeBase64(const char* encoded)
	{
		return decodeBase64(std::string(encoded));
	}

	std::vector<uint8_t> decodeBase64(const std::string& encoded)
	{
		std::vector<uint8_t> decoded;
		size_t				 encodedIndex = 0;
		while (encodedIndex < encoded.size())
		{
			uint8_t out[3]   = {0, 0, 0};
			size_t  gathered = 0;
			for (gathered = 0; gathered < 4; gathered++)
			{
				// Check, if out of bounds. If yes, invalid encoded.
				if (encodedIndex >= encoded.size())
				{
					return std::vector<uint8_t>();
				}

				size_t index = base64Characters.find(encoded[encodedIndex]);

				// Check, if BASE64 character. If not, invalid encoded.
				if (index == base64Characters.npos && encoded[encodedIndex] != '=')
				{
					return std::vector<uint8_t>();
				}

				if (encoded[encodedIndex] == '=')
				{
					break;
				}

				uint8_t in = (uint8_t)index;

				if (gathered == 0)
				{
					out[0] = in << 2;
				}
				else if (gathered == 1)
				{
					out[0] |= in >> 4;

					out[1] = (in << 4) & 0xF0;
				}
				else if (gathered == 2)
				{
					out[1] |= in >> 2;

					out[2] = (in << 6) & 0xC0;
				}
				else if (gathered == 3)
				{
					out[2] |= in;
				}

				encodedIndex++;
			}

			//

			for (size_t i = 0; i < 3; i++)
			{
				if (gathered != 4 && i == 2)
				{
					return decoded;
				}

				decoded.push_back(out[i]);
			}
		}

		return decoded;
	}

	//---
	// converts data to base64 string
	// NOTE: only base64 string, NOT data uri

	std::string encodeBase64(const uint8_t* const data, size_t size)
	{
		return encodeBase64(std::vector<uint8_t>(data, data + size));
	}

	std::string encodeBase64(const std::vector<uint8_t>& data)
	{
		std::string encoded   = "";
		size_t		dataIndex = 0;
		while (dataIndex < data.size())
		{
			uint8_t in[3]	= {0, 0, 0};
			size_t  gathered = 0;
			for (gathered = 0; gathered < 3; gathered++)
			{
				if (dataIndex == data.size())
				{
					break;
				}

				in[gathered] = data[dataIndex];

				//

				dataIndex++;
			}

			//

			uint8_t out[4] = {0, 0, 0, 0};

			out[0] = (in[0] >> 2) & 0x3F;
			out[1] = ((in[0] << 4) & 0x30) | ((in[1] >> 4) & 0x0F);

			if (gathered >= 2)
			{
				out[2] = (in[1] << 2) & 0x3C;

				if (gathered == 3)
				{
					out[2] |= (in[2] >> 6) & 0x03;
					out[3] = in[2] & 0x3F;
				}
			}

			//

			for (uint32_t i = 0; i < 4; i++)
			{
				if (gathered >= i)
				{
					encoded.push_back(base64Characters[out[i]]);
				}
				else
				{
					encoded.push_back('=');
				}
			}
		}

		return encoded;
	}

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_common
