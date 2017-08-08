#include "flatgltf/2.0/glTFio.hpp"
#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/common/glTFutils.hpp"
#include "glTFinternal.hpp"

#include "flatbuffers/flatbuffers.h"
#include "flatbuffers/idl.h"

#define KHUTILS_ASSERTION_INLINE
#include "khutils/assertion.hpp"
#include "khutils/file.hpp"
#include "khutils/logging.hpp"
#include "khutils/runtime_exceptions.hpp"

/// terribly sorry for this dependency. will remove asap
#include <boost/filesystem/path.hpp>


#include <algorithm>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

// flatbuffer schema string for parser
extern const std::string flatgltf_2_0_schema;


namespace glTF_2_0
{
	using namespace glTF_common;

	///------------------------------------------------------------------------
	/// load document as-is, without modification or external data
	///------------------------------------------------------------------------

	inline void initializeDocument(Document* const doc, Root_t&& root)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(root);

		doc->root.swap(root);
		doc->bindata.clear();
		doc->imgdata.clear();
	}

	//---

	// load document as-is, without modification or external data
	bool loadDocument_json(Document* const doc, const char* location, data_reader_t reader)
	{
		KHUTILS_ASSERT_PTR(doc);

		std::vector<uint8_t> buffer;
		auto				 readOk = reader(location, buffer);

		if (readOk)
		{
			KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);
			std::string jsonString(reinterpret_cast<const char*>(buffer.data()), buffer.size());
			initializeDocument(doc, from_json_internal(jsonString));
			return true;
		}

		return false;
	}

	//---

	bool loadDocument_glf(Document* const doc, const char* location, data_reader_t reader)
	{
		std::vector<uint8_t> buffer;
		auto				 readOk = reader(location, buffer);

		if (readOk)
		{
			KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);
			initializeDocument(doc, from_flatbuffer_internal(buffer));
			return true;
		}

		return false;
	}

	//---

	// loadDocument_glb implemented further below

	//-------------------------------------------------------------------------

	///------------------------------------------------------------------------
	/// load document: transform data uris to buffers, load external resources
	///------------------------------------------------------------------------

	bool loadDocument_dataAndReferences(Document* const doc, const char* location, data_reader_t reader)
	{
		KHUTILS_ASSERT_PTR(doc);

		bool allBuffersLoadOk = std::all_of(doc->root->buffers.begin(), doc->root->buffers.end(), [&](auto& buf) {
			if (isDataUri(buf->uri))
			{
				setBufferData(convertUriToData(buf->uri), doc, buf.get());
				return true;
			}

			std::vector<uint8_t>bufData;
			if (reader(buf->uri.c_str(), bufData))
			{
				setBufferData(bufData, doc, buf.get());
				return true;
			}
			return false;
		});


		bool allImagesLoadOk = std::all_of(doc->root->images.begin(), doc->root->images.end(), [&](auto& img) {
			if (isValidBufferViewId(doc, img->bufferView))
				return true;

			if (isDataUri(img->uri))
			{
				setImageData(convertUriToData(img->uri), doc, img.get());
				return true;
			}

			std::vector<uint8_t>bufData;
			if (reader(img->uri.c_str(), bufData))
			{
				setImageData(bufData, doc, img.get());
				return true;
			}
			return false;
		});

		return allBuffersLoadOk && allImagesLoadOk;
	}

	//---

	// load document: transform data uris to buffers, load external resources
	bool loadDocument_json_plus(Document* const doc, const char* location, data_reader_t reader)
	{
		return loadDocument_json(doc, location, reader) &&	//
			   loadDocument_dataAndReferences(doc, location, reader);
	}

	//---

	bool loadDocument_glf_plus(Document* const doc, const char* location, data_reader_t reader)
	{
		return loadDocument_glf(doc, location, reader) &&	//
			   loadDocument_dataAndReferences(doc, location, reader);
	}

	//---

	// load document from glTF-binary: all buffers merged into 1, with external data
	bool loadDocument_glb_plus(Document* const doc, const char* location, data_reader_t reader)
	{
		return loadDocument_glb(doc, location, reader) &&	//
			   loadDocument_dataAndReferences(doc, location, reader);
	}

	//-------------------------------------------------------------------------


	///------------------------------------------------------------------------
	/// write document as-is, without modification or external data
	///------------------------------------------------------------------------

	bool saveDocument_json(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto jsonString = to_json(doc->root);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(jsonString);

		std::vector<uint8_t> buffer;
		buffer.reserve(jsonString.size());
		std::transform(jsonString.begin(), jsonString.end(), std::back_inserter(buffer), [](auto& c) {
			return static_cast<uint8_t>(c);
		});

		return writer(location, buffer);
	}

	//---

	bool saveDocument_glf(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto buffer = to_flatbuffer(doc->root);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);

		return writer(location, buffer);
	}

	//---

	// bool saveDocument_glb implemented further below

	///------------------------------------------------------------------------
	/// write document as-is, write buffers and images set to external URIs
	///------------------------------------------------------------------------

	bool saveDocument_buffers(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		return std::all_of(doc->root->buffers.begin(), doc->root->buffers.end(), [&](auto& buf) {
			if (isDataUri(buf->uri))
				return true;

			return writer(buf->uri.c_str(), getBufferData(doc, buf.get()));
		});
	}

	//---

	bool saveDocument_images(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		return std::all_of(doc->root->images.begin(), doc->root->images.end(), [&](auto& img) {
			if (isDataUri(img->uri))
				return true;

			if (isValidBufferViewId(doc, img->bufferView))
				return true;

			return writer(img->uri.c_str(), getImageData(doc, img.get()));
		});
	}

	//---

	bool saveDocument_dataAndReferences(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);
		return saveDocument_buffers(doc, location, writer) && saveDocument_images(doc, location, writer);
	}

	//---

	bool saveDocument_json_plus(const Document* const doc, const char* location, data_writer_t writer)
	{
		return saveDocument_json(doc, location, writer) &&	//
			   saveDocument_dataAndReferences(doc, location, writer);
	}

	//---

	bool saveDocument_glf_plus(const Document* const doc, const char* location, data_writer_t writer)
	{
		return saveDocument_glf(doc, location, writer) &&	//
			   saveDocument_dataAndReferences(doc, location, writer);
	}

	//---

	bool saveDocument_glb_plus(const Document* const doc, const char* location, data_writer_t writer)
	{
		return saveDocument_glb(doc, location, writer) &&	 //
			   saveDocument_images(doc, location, writer);	// only external images, buffer is already written
	}

	//-------------------------------------------------------------------------


	///------------------------------------------------------------------------
	/// write document: ALL buffers/images will be embedded base64 URIs
	///------------------------------------------------------------------------

	bool saveDocument_json_embed(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto embeddedRoot = embedDocumentBuffersAndImages(doc);
		KHUTILS_ASSERT_PTR(embeddedRoot);

		auto jsonString = to_json(embeddedRoot);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(jsonString);

		std::vector<uint8_t> buffer;
		buffer.reserve(jsonString.size());
		std::transform(jsonString.begin(), jsonString.end(), std::back_inserter(buffer), [](auto& c) {
			return static_cast<uint8_t>(c);
		});

		return writer(location, buffer);
	}

	//---

	bool saveDocument_glf_embed(const Document* const doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto embeddedRoot = embedDocumentBuffersAndImages(doc);
		KHUTILS_ASSERT_PTR(embeddedRoot);

		auto buffer = to_flatbuffer(embeddedRoot);
		KHUTILS_ASSERT_CNTR_NOT_EMPTY(buffer);

		return writer(location, buffer);
	}

	//-------------------------------------------------------------------------


	///------------------------------------------------------------------------
	/// write document: ALL buffers/images will be external files named after URI or name or counter
	///------------------------------------------------------------------------

	bool saveDocument_json_external(const Document* const _doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocument("copy");

		return cloneDocument(_doc, doc) &&	//
			   dislodgeDocument(doc) &&		  //
			   saveDocument_json_plus(doc, location, writer);
	}

	//---

	bool saveDocument_glf_external(const Document* const _doc, const char* location, data_writer_t writer)
	{
		KHUTILS_ASSERT_PTR(_doc);
		auto doc = createDocument("copy");

		return cloneDocument(_doc, doc) &&	//
			   dislodgeDocument(doc) &&		  //
			   saveDocument_glf_plus(doc, location, writer);
	}

	//-------------------------------------------------------------------------

	///------------------------------------------------------------------------
	/// ease-of-use load/save functions, to file by default
	///------------------------------------------------------------------------

	namespace fs = boost::filesystem;

	bool loadDocument(Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto p = fs::path(uri);
		if (p.extension() == ".glb")
		{
			return loadDocument_glb_plus(doc, uri);
		}

		if (p.extension() == ".glf")
		{
			return loadDocument_glf_plus(doc, uri);
		}

		if (p.extension() == ".gltf")
		{
			return loadDocument_json_plus(doc, uri);
		}

		return false;
	}

	//---

	bool saveDocument(const Document* const doc, const char* uri)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto p = fs::path(uri);
		if (p.extension() == ".glb")
		{
			return saveDocument_glb_plus(doc, uri);
		}

		if (p.extension() == ".glf")
		{
			return saveDocument_glf_plus(doc, uri);
		}

		if (p.extension() == ".gltf")
		{
			return saveDocument_json_plus(doc, uri);
		}

		return false;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
