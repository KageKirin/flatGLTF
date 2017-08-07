#include "flatgltf/common/glTFutils.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/file.hpp"
#include "khutils/runtime_exceptions.hpp"


#include <cctype>
#include <cstdio>
#include <regex>
#include <string>
#include <vector>

namespace glTF_common
{
	///-----------------------------------------------------------------------
	/// Common IO
	///-----------------------------------------------------------------------

	bool writeData(const char* location, const std::vector<uint8_t>& data)
	{
		auto file = khutils::openLocalFilePtr(location, "wb");
		if (file)
		{
			khutils::dumpBufferToFile(data, file);
			return true;
		}
		return false;
	}

	bool readData(const char* location, std::vector<uint8_t>& data)
	{
		auto file = khutils::openLocalFilePtr(location, "rb");
		if (file)
		{
			auto buf = khutils::openBufferFromFile(file);
			data.assign(buf.begin(), buf.end());
			return true;
		}
		return false;
	}

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_common
