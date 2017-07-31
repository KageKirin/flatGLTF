#ifndef FLATGLTF_2_0_INTERNAL_TYPES_H_INC
#define FLATGLTF_2_0_INTERNAL_TYPES_H_INC

#include "glTF_generated.h"
#include "glTF_math_types.h"

#include <cctype>
#include <memory>
#include <string>
#include <vector>

namespace glTF_2_0
{
	namespace detail
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

	}	// namespace detail

	//! container structure to keep glTF data along with buffers
	struct glTF_Document
	{
		detail::Root_t								root;
		std::map<std::string, std::vector<uint8_t>> bindata;
	};

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_INTERNAL_TYPES_H_INC
