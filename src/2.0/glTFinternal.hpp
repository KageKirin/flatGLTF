#ifndef FLATGLTF_2_0_INTERNAL_TYPES_H_INC
#define FLATGLTF_2_0_INTERNAL_TYPES_H_INC

#include "glTF_generated.h"
#include "glTFmath_types.hpp"

#include <cctype>
#include <memory>
#include <string>
#include <vector>

namespace glTF_2_0
{
	//---
	using AccessorSparseIndices_t		 = std::unique_ptr<AccessorSparseIndicesT>;
	using AccessorSparseValues_t		 = std::unique_ptr<AccessorSparseValuesT>;
	using AccessorSparse_t				 = std::unique_ptr<AccessorSparseT>;
	using Accessor_t					 = std::unique_ptr<AccessorT>;
	using Asset_t						 = std::unique_ptr<AssetT>;
	using AnimationChannelTarget_t		 = std::unique_ptr<AnimationChannelTargetT>;
	using AnimationChannel_t			 = std::unique_ptr<AnimationChannelT>;
	using AnimationSampler_t			 = std::unique_ptr<AnimationSamplerT>;
	using Animation_t					 = std::unique_ptr<AnimationT>;
	using Buffer_t						 = std::unique_ptr<BufferT>;
	using BufferView_t					 = std::unique_ptr<BufferViewT>;
	using CameraOrthographic_t			 = std::unique_ptr<CameraOrthographicT>;
	using CameraPerspective_t			 = std::unique_ptr<CameraPerspectiveT>;
	using Camera_t						 = std::unique_ptr<CameraT>;
	using Image_t						 = std::unique_ptr<ImageT>;
	using TextureInfo_t					 = std::unique_ptr<TextureInfoT>;
	using MaterialNormalTextureInfo_t	= std::unique_ptr<MaterialNormalTextureInfoT>;
	using MaterialOcclusionTextureInfo_t = std::unique_ptr<MaterialOcclusionTextureInfoT>;
	using MaterialPbrMetallicRoughness_t = std::unique_ptr<MaterialPbrMetallicRoughnessT>;
	using Material_t					 = std::unique_ptr<MaterialT>;
	using MeshPrimitive_t				 = std::unique_ptr<MeshPrimitiveT>;
	using Mesh_t						 = std::unique_ptr<MeshT>;
	using Node_t						 = std::unique_ptr<NodeT>;
	using Scene_t						 = std::unique_ptr<SceneT>;
	using Sampler_t						 = std::unique_ptr<SamplerT>;
	using Texture_t						 = std::unique_ptr<TextureT>;
	using Skin_t						 = std::unique_ptr<SkinT>;
	using Root_t						 = std::unique_ptr<RootT>;

	//---
	//! container structure to keep glTF data along with buffers
	struct Document
	{
		/// json root element for glTF data
		Root_t root;

		/// binary data mapping buffer -> data referenced by buffer elements
		std::map<BufferT* const, std::vector<uint8_t>> bindata;

		/// binary data mapping image -> image data referenced by image elements
		/// NOTE: images can rerefence bufferViews, and thus buffer,
		/// in which case the image data will be stored in the referenced buffer
		std::map<ImageT* const, std::vector<uint8_t>> imgdata;
	};

	std::unique_ptr<Document, decltype(&destroyDocument)> createDocumentPtr(const std::string& name);

	// creates new bindata
	std::vector<uint8_t>& createBufferData(Document* const, BufferT* const);

	// creates new imgdata
	std::vector<uint8_t>& createImageData(Document* const, ImageT* const);

	///-----------------------------------------------------------------------

	//! marshal glTF object to JSON
	std::string to_json(const Root_t&);
	//! unmarshal glTF object form JSON
	Root_t from_json_internal(const std::string&);

	//! flatbuffer-serialize glTF object to buffer
	std::vector<uint8_t> to_flatbuffer(const Root_t&);
	//! flatbuffer-deserialize glTF object from buffer
	Root_t from_flatbuffer_internal(const std::vector<uint8_t>&);

	///-----------------------------------------------------------------------

	Root_t cloneRoot(const Root_t& orig);

	Root_t embedDocumentImages(const Document* const);
	Root_t embedDocumentBuffersAndImages(const Document* const);

	std::tuple<Root_t, std::vector<uint8_t>> binarizeDocumentBuffers(const Document* const _doc, bool withImages);
	std::tuple<Root_t, std::vector<uint8_t>> binarizeDocumentBuffers_embedImages(const Document* const _doc, bool withImages);


	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	bool binarizeDocument(Document* const);

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	bool embedDocument(Document* const);

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	bool dislodgeDocument(Document* const);

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	bool splitDocument(Document* const);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_INTERNAL_TYPES_H_INC
