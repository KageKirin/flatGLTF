#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

#include <algorithm>
#include <vector>

namespace glTF_2_0
{
	///-----------------------------------------------------------------------
	/// get-id
	///-----------------------------------------------------------------------
	// all functions return a glTFid_t >= 0 if found, < 0 if not

	glTFid_t getId(const Document* const doc, const AccessorT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->accessors.begin(), doc->root->accessors.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->accessors.end())
			{
				return glTFid_t(std::distance(doc->root->accessors.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const AnimationT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->animations.begin(), doc->root->animations.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->animations.end())
			{
				return glTFid_t(std::distance(doc->root->animations.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const BufferT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->buffers.begin(), doc->root->buffers.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->buffers.end())
			{
				return glTFid_t(std::distance(doc->root->buffers.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const BufferViewT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->bufferViews.begin(), doc->root->bufferViews.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->bufferViews.end())
			{
				return glTFid_t(std::distance(doc->root->bufferViews.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const CameraT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->cameras.begin(), doc->root->cameras.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->cameras.end())
			{
				return glTFid_t(std::distance(doc->root->cameras.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const ImageT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->images.begin(), doc->root->images.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->images.end())
			{
				return glTFid_t(std::distance(doc->root->images.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const MaterialT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->materials.begin(), doc->root->materials.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->materials.end())
			{
				return glTFid_t(std::distance(doc->root->materials.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const MeshT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->meshes.begin(), doc->root->meshes.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->meshes.end())
			{
				return glTFid_t(std::distance(doc->root->meshes.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const NodeT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->nodes.begin(), doc->root->nodes.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->nodes.end())
			{
				return glTFid_t(std::distance(doc->root->nodes.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const SceneT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->scenes.begin(), doc->root->scenes.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->scenes.end())
			{
				return glTFid_t(std::distance(doc->root->scenes.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const SamplerT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->samplers.begin(), doc->root->samplers.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->samplers.end())
			{
				return glTFid_t(std::distance(doc->root->samplers.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const TextureT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->textures.begin(), doc->root->textures.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->textures.end())
			{
				return glTFid_t(std::distance(doc->root->textures.begin(), it));
			}
		}
		return -1;
	}

	//---

	glTFid_t getId(const Document* const doc, const SkinT* const elem)
	{
		if (!elem)
		{
			return -2;
		}
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->skins.begin(), doc->root->skins.end(), [&elem](auto& inst) {
				return inst.get() == elem;
			});
			if (it != doc->root->skins.end())
			{
				return glTFid_t(std::distance(doc->root->skins.begin(), it));
			}
		}
		return -1;
	}

	//---

	///-----------------------------------------------------------------------
	/// validate-id
	///-----------------------------------------------------------------------
	// all functions return true if id is valid for this document and type

	bool isValidAccessorId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->accessors.size());
	}

	//---

	bool isValidAnimationId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->animations.size());
	}

	//---

	bool isValidBufferId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->buffers.size());
	}

	//---

	bool isValidBufferViewId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->bufferViews.size());
	}

	//---

	bool isValidCameraId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->cameras.size());
	}

	//---

	bool isValidImageId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->images.size());
	}

	//---

	bool isValidMaterialId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->materials.size());
	}

	//---

	bool isValidMeshId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->meshes.size());
	}

	//---

	bool isValidNodeId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->nodes.size());
	}

	//---

	bool isValidSceneId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->scenes.size());
	}

	//---

	bool isValidSamplerId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->samplers.size());
	}

	//---

	bool isValidTextureId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->textures.size());
	}

	//---

	bool isValidSkinId(const Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		return (id >= 0) && (id < (glTFid_t)doc->root->skins.size());
	}

	//---


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
