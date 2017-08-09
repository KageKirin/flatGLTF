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

	///-----------------------------------------------------------------------
	/// image data type check
	///-----------------------------------------------------------------------

	inline bool isImageDataJPEG(const uint8_t* buffer, size_t len)
	{
		constexpr uint8_t magic[]	 = {0xff, 0xd8, 0xff};
		constexpr size_t  sizeOfMagic = sizeof(magic);

		if (len < sizeOfMagic)
			return false;

		return buffer[0] == magic[0] &&	//
			   buffer[1] == magic[1] &&	//
			   buffer[2] == magic[2];
	}

	inline bool isImageDataJPEG(const std::vector<uint8_t>& buffer)
	{
		return isImageDataJPEG(buffer.data(), buffer.size());
	}

	//---

	inline bool isImageDataPNG(const uint8_t* buffer, size_t len)
	{
		constexpr uint8_t magic[]	 = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a};
		constexpr size_t  sizeOfMagic = sizeof(magic);

		if (len < sizeOfMagic)
			return false;

		return buffer[0] == magic[0] &&	//
			   buffer[1] == magic[1] &&	//
			   buffer[2] == magic[2] &&	//
			   buffer[3] == magic[3] &&	//
			   buffer[4] == magic[4] &&	//
			   buffer[5] == magic[5] &&	//
			   buffer[6] == magic[6] &&	//
			   buffer[7] == magic[7];
	}

	inline bool isImageDataPNG(const std::vector<uint8_t>& buffer)
	{
		return isImageDataPNG(buffer.data(), buffer.size());
	}

	///-----------------------------------------------------------------------
	/// cloning
	///-----------------------------------------------------------------------

	Root_t cloneRoot(const Root_t& orig)
	{
		return from_flatbuffer_internal(to_flatbuffer(orig));
	}

	//---

	/// clone a document into a new one
	bool cloneDocument(const Document* const source, Document* const target)
	{
		KHUTILS_ASSERT_PTR(source);
		KHUTILS_ASSERT_PTR(target);

		auto newRoot = cloneRoot(source->root);
		target->root.swap(newRoot);
		target->bindata.clear();
		std::copy(source->bindata.begin(),
				  source->bindata.end(),
				  std::insert_iterator<decltype(target->bindata)>(target->bindata, target->bindata.end()));

		return true;
	}

	//-------------------------------------------------------------------------

	Root_t embedDocumentImages(const Document* const _doc)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocumentPtr("copy");
		KHUTILS_ASSERT_PTR(doc);
		auto copyOk = cloneDocument(_doc, doc.get());
		KHUTILS_ASSERT(copyOk);

		for (auto& idp : doc->imgdata)
		{
			KHUTILS_ASSERT(isValidImageId(doc.get(), idp.first));
			auto img = getImage(doc.get(), idp.first);
			KHUTILS_ASSERT_PTR(img);

			if (isImageDataPNG(idp.second))
				img->uri = convertDataToUri(idp.second, "image/png");
			else if (isImageDataJPEG(idp.second))
				img->uri = convertDataToUri(idp.second, "image/jpeg");
			else	// actually not in spec
				img->uri = convertDataToUri(idp.second, "application/octet-stream");
		}

		return std::move(doc->root);
	}

	//---

	Root_t embedDocumentBuffersAndImages(const Document* const _doc)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocumentPtr("copy");
		KHUTILS_ASSERT_PTR(doc);
		auto copyOk = cloneDocument(_doc, doc.get());
		KHUTILS_ASSERT(copyOk);

		for (auto& bdp : doc->bindata)
		{
			KHUTILS_ASSERT(isValidBufferId(doc.get(), bdp.first));
			auto buf = getBuffer(doc.get(), bdp.first);
			KHUTILS_ASSERT_PTR(buf);

			buf->uri = convertDataToUri(bdp.second, "application/octet-stream");
		}

		for (auto& idp : doc->imgdata)
		{
			KHUTILS_ASSERT(isValidImageId(doc.get(), idp.first));
			auto img = getImage(doc.get(), idp.first);
			KHUTILS_ASSERT_PTR(img);

			if (isImageDataPNG(idp.second))
				img->uri = convertDataToUri(idp.second, "image/png");
			else if (isImageDataJPEG(idp.second))
				img->uri = convertDataToUri(idp.second, "image/jpeg");
			else	// actually not in spec
				img->uri = convertDataToUri(idp.second, "application/octet-stream");
		}

		return std::move(doc->root);
	}

	//-------------------------------------------------------------------------
	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly

	std::tuple<Root_t, std::vector<uint8_t>> binarizeDocumentBuffers(const Document* const _doc, bool withImages)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocumentPtr("copy");
		KHUTILS_ASSERT_PTR(doc);
		auto copyOk = cloneDocument(_doc, doc.get());
		KHUTILS_ASSERT(copyOk);

		if (withImages)
		{
			auto buf = createBuffer(doc.get(), "extra_imagedatabuffer");
			for (auto& img : doc->root->images)
			{
				// check if already handled
				if (isValidBufferViewId(doc.get(), img->bufferView))
					continue;

				// create new bufferviews for image
				auto imgdata = getImageData(doc.get(), img.get());
				KHUTILS_ASSERT_CNTR_NOT_EMPTY(imgdata);

				auto view = createBufferView(imgdata, doc.get(), buf, (img->name + "_buffer").c_str());
				KHUTILS_ASSERT_PTR(view);

				img->bufferView = getId(doc.get(), view);
			}
		}

		std::vector<uint8_t> buffer;
		for (auto& view : doc->root->bufferViews)
		{
			auto viewdata = getBufferViewData(doc.get(), view.get());

			view->buffer	 = 0;
			view->byteOffset = buffer.size();
			buffer.reserve(buffer.size() + viewdata.size());
			std::copy(viewdata.begin(), viewdata.end(), std::back_inserter(buffer));
		}

		auto root = cloneRoot(doc->root);
		root->buffers.resize(1);
		root->buffers[0]->uri		 = "";
		root->buffers[0]->byteLength = buffer.size();

		return std::tuple<Root_t, std::vector<uint8_t>>{std::move(root), std::move(buffer)};
	}

	//---

	std::tuple<Root_t, std::vector<uint8_t>> binarizeDocumentBuffers_embedImages(const Document* const _doc, bool withImages)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocumentPtr("copy");
		KHUTILS_ASSERT_PTR(doc);
		auto copyOk = cloneDocument(_doc, doc.get());
		KHUTILS_ASSERT(copyOk);

		if (withImages)
		{
			for (auto& idp : doc->imgdata)
			{
				KHUTILS_ASSERT(isValidImageId(doc.get(), idp.first));
				auto img = getImage(doc.get(), idp.first);
				KHUTILS_ASSERT_PTR(img);

				if (isImageDataPNG(idp.second))
					img->uri = convertDataToUri(idp.second, "image/png");
				else if (isImageDataJPEG(idp.second))
					img->uri = convertDataToUri(idp.second, "image/jpeg");
				else	// actually not in spec
					img->uri = convertDataToUri(idp.second, "application/octet-stream");
			}
		}

		std::vector<uint8_t> buffer;
		for (auto& view : doc->root->bufferViews)
		{
			auto viewdata = getBufferViewData(doc.get(), view.get());

			view->buffer	 = 0;
			view->byteOffset = buffer.size();
			buffer.reserve(buffer.size() + viewdata.size());
			std::copy(viewdata.begin(), viewdata.end(), std::back_inserter(buffer));
		}

		auto root = cloneRoot(doc->root);
		if (root->buffers.size() > 1)
		{
			std::remove_if(root->buffers.begin() + 1, root->buffers.end(), [](auto&) { return true; });
		}
		root->buffers[0]->uri		 = "";
		root->buffers[0]->byteLength = buffer.size();

		return std::tuple<Root_t, std::vector<uint8_t>>{std::move(root), std::move(buffer)};
	}


	//-------------------------------------------------------------------------

	bool binarizeDocument(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);

		Root_t				 root;
		std::vector<uint8_t> bindata;
		std::tie(root, bindata) = binarizeDocumentBuffers(doc, false);
		KHUTILS_ASSERT_PTR(root);

		doc->root.swap(root);
		doc->bindata.clear();
		doc->bindata[0].assign(bindata.begin(), bindata.end());

		return true;
	}

	//---

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	bool embedDocument(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);
		auto root = embedDocumentBuffersAndImages(doc);
		KHUTILS_ASSERT_PTR(root);

		doc->root.swap(root);
		doc->bindata.clear();
		doc->imgdata.clear();

		return true;
	}

	//---

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	bool dislodgeDocument(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);

		size_t bindataCounter = 0;

		for (auto& bdp : doc->bindata)
		{
			KHUTILS_ASSERT(isValidBufferId(doc, bdp.first));
			auto buf = getBuffer(doc, bdp.first);
			KHUTILS_ASSERT_PTR(buf);
			if (isDataUri(buf->uri))
			{
				buf->uri = std::string("bindata") + std::to_string(bindataCounter++) + ".bin";
			}
		}

		size_t imgdataCounter = 0;
		for (auto& idp : doc->imgdata)
		{
			KHUTILS_ASSERT(isValidImageId(doc, idp.first));
			auto img = getImage(doc, idp.first);
			KHUTILS_ASSERT_PTR(img);
			if (isDataUri(img->uri))
			{
				img->uri = std::string("imgdata") + std::to_string(imgdataCounter++);

				if (isImageDataPNG(idp.second))
					img->uri += ".png";
				else if (isImageDataJPEG(idp.second))
					img->uri += ".jpeg";
				else	// actually not in spec
					img->uri += ".bin";
			}
		}

		return true;
	}

	//---

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	bool splitDocument(Document* const doc)
	{
		KHUTILS_ASSERT_PTR(doc);


		return false;
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
