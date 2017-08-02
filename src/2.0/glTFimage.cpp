#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/common/glTFutils.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	using namespace glTF_common;

	//-------------------------------------------------------------------------

	SamplerT* const createSampler_withDefaults(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto sam = createSampler(doc);
		KHUTILS_ASSERT_PTR(sam);

		sam->magFilter = SamplerFilter::LINEAR;
		sam->minFilter = SamplerFilter::LINEAR;
		sam->wrapS	 = WrapMode::CLAMP_TO_EDGE;
		sam->wrapT	 = WrapMode::CLAMP_TO_EDGE;

		return sam;
	}

	//---

	TextureT* const createTexture(Document* const doc, ImageT* const image)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(image);

		auto tex = createTexture(doc, (image->uri + "tex").c_str());
		KHUTILS_ASSERT_PTR(tex);
		tex->source = getId(doc, image);

		return tex;
	}

	//---

	//! create an image referring to a buffer view for data
	ImageT* const createImage(Document* const doc, BufferViewT* const view, const char* mimeType, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(view);
		KHUTILS_ASSERT_PTR(mimeType);

		auto img = createImage(doc, name);
		KHUTILS_ASSERT_PTR(img);

		img->mimeType   = mimeType;
		img->bufferView = getId(doc, view);

		return img;
	}

	//---

	//! create an image referring to a uri

	ImageT* const createImage(Document* const doc, const char* uri, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(uri);

		auto img = createImage(doc, name);
		KHUTILS_ASSERT_PTR(img);

		img->uri = uri;

		return img;
	}

	//---

	//! create an image referring to a base64 uri created from provided data
	ImageT* const createImage_embedded(const std::vector<uint8_t>& data, Document* const doc, const char* mimeType, const char* name)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return createImage_embedded(data.data(), data.size(), doc, mimeType, name);
	}

	//---

	ImageT* const createImage_embedded(const uint8_t* const data, size_t length, Document* const doc, const char* mimeType, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(data);
		KHUTILS_ASSERT_PTR(mimeType);

		auto uri = convertDataToUri(data, length, mimeType);
		return createImage(doc, uri.c_str(), name);
	}

	//---

	ImageT* const createImage(const std::vector<uint8_t>& data, Document* const doc, const char* uri, const char* name)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return createImage(data.data(), data.size(), doc, uri, name);
	}

	//---

	ImageT* const createImage(const uint8_t* const data, size_t length, Document* const doc, const char* uri, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(data);
		KHUTILS_ASSERT_PTR(uri);
		KHUTILS_ASSERT(!isDataUri(uri));

		auto img = createImage(doc, uri, name);
		KHUTILS_ASSERT_PTR(img);

		doc->imgdata[uri].clear();
		doc->imgdata[uri].reserve(length);
		std::copy_n(data, length, std::back_inserter(doc->imgdata[uri]));

		return img;
	}

	//---

	std::vector<uint8_t>* const createImgdata(Document* const doc, const char* name)
	{
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
