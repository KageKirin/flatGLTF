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

	ImageT* const createImage(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto instance = Image_t{new ImageT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->images.push_back(std::move(instance));
		createImageData(doc, instance.get()).clear();
		return doc->root->images.back().get();
	}

	//---

	//! create an image referring to a uri
	ImageT* const createImage(Document* const doc, const char* uri, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(uri);

		auto image = createImage(doc, name);
		image->uri = uri;

		if (isDataUri(image->uri))
		{
			setImageData(convertUriToData(uri), doc, image);
			image->uri = setUriBase64(uri, "");	// remove data, as its decoded in image now
		}

		return image;
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

	//! create an image referring to an external file uri, data kept in imgdata
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

		auto img = createImage(doc, uri, name);
		KHUTILS_ASSERT_PTR(img);

		auto setLength = setImageData(data, length, doc, img);
		KHUTILS_ASSERT_EQUALS(setLength, length);

		return img;
	}

	///-----------------------------------------------------------------------
	/// imgdata
	///-----------------------------------------------------------------------

	std::vector<uint8_t>& createImageData(Document* const doc, ImageT* const img)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(img);

		doc->imgdata[img].clear();
		return doc->imgdata[img];
	}

	//---

	std::vector<uint8_t>& getImageData(Document* const doc, ImageT* const img)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(img);

		auto id = getId(doc, img);
		KHUTILS_ASSERT(isValidImageId(doc, id));

		// TODO: handle case of bufferView-stored data
		// --> has side effects due to next functions
		// --> currently, we cannot get/modify this data, hence assert below
		KHUTILS_ASSERT(!isValidBufferViewId(doc, img->bufferView));

		auto it = std::find_if(doc->imgdata.begin(), doc->imgdata.end(), [&](auto& bdp) { return bdp.first == img; });
		KHUTILS_ASSERT_NOT(it, doc->imgdata.end());

		return it->second;
	}

	//---
	// sets image data, overwriting existing
	// returns new size
	// returns 0 if: image does not exist

	size_t setImageData(const std::vector<uint8_t>& data, Document* const doc, ImageT* const img)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return setImageData(data.data(), data.size(), doc, img);
	}

	//---

	size_t setImageData(const uint8_t* data, size_t length, Document* const doc, ImageT* const img)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(img);

		auto id = getId(doc, img);
		if (isValidImageId(doc, id))
		{
			auto imgdata = getImageData(doc, img);
			imgdata.clear();
			imgdata.reserve(length);
			std::copy_n(data, length, std::back_inserter(imgdata));
			return getImageData(doc, img).size();
		}

		return 0;
	}

	//---
	// appends image data to existing image data
	// returns new size
	// returns 0 if: image does not exist

	size_t appendImageData(const std::vector<uint8_t>& data, Document* const doc, ImageT* const img)
	{
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(data);
		return appendImageData(data.data(), data.size(), doc, img);
	}

	//---

	size_t appendImageData(const uint8_t* data, size_t length, Document* const doc, ImageT* const img)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(img);

		auto id = getId(doc, img);
		if (isValidImageId(doc, id))
		{
			auto imgdata = getImageData(doc, img);
			imgdata.reserve(imgdata.size() + length);
			std::copy_n(data, length, std::back_inserter(imgdata));
			return getImageData(doc, img).size();
		}

		return 0;
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
