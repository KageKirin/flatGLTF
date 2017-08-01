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
	/// simple get for unique elements
	///-----------------------------------------------------------------------

	AssetT* const getAsset(const Document* const doc)
	{
		return (doc && doc->root) ? doc->root->asset.get() : nullptr;
	}

	SceneT* const getMainScene(const Document* const doc)
	{
		return (doc && doc->root) ? getScene(doc, doc->root->scene) : nullptr;
	}

	void setMainScene(Document* const doc, SceneT* const scene)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(scene);
		setMainScene(doc, getId(doc, scene));
	}

	void setMainScene(Document* const doc, glTFid_t id)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_GREATEREQ(id, 0);
		doc->root->scene = id;
	}

	///-----------------------------------------------------------------------
	/// get-by-id
	///-----------------------------------------------------------------------

	AccessorT* const getAccessor(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->accessors.size())
				return doc->root->accessors[id].get();
		}
		return nullptr;
	}

	//---

	AnimationT* const getAnimation(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->animations.size())
				return doc->root->animations[id].get();
		}
		return nullptr;
	}

	//---

	BufferT* const getBuffer(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->buffers.size())
				return doc->root->buffers[id].get();
		}
		return nullptr;
	}

	//---

	BufferViewT* const getBufferView(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->bufferViews.size())
				return doc->root->bufferViews[id].get();
		}
		return nullptr;
	}

	//---

	CameraT* const getCamera(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->cameras.size())
				return doc->root->cameras[id].get();
		}
		return nullptr;
	}

	//---

	ImageT* const getImage(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->images.size())
				return doc->root->images[id].get();
		}
		return nullptr;
	}

	//---

	MaterialT* const getMaterial(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->materials.size())
				return doc->root->materials[id].get();
		}
		return nullptr;
	}

	//---

	// MeshPrimitiveT *const getMeshPrimitive(const Document* const doc, glTFid_t id)
	//{
	//	if (doc && doc->root)
	//	{
	//		if (id >= 0 && id < doc->root->meshprimitives.size())
	//			return doc->root->meshprimitives[id].get();
	//	}
	//	return nullptr;
	//}

	//---

	MeshT* const getMesh(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->meshes.size())
				return doc->root->meshes[id].get();
		}
		return nullptr;
	}

	//---

	NodeT* const getNode(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->nodes.size())
				return doc->root->nodes[id].get();
		}
		return nullptr;
	}

	//---

	SceneT* const getScene(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->scenes.size())
				return doc->root->scenes[id].get();
		}
		return nullptr;
	}

	//---

	SamplerT* const getSampler(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->samplers.size())
				return doc->root->samplers[id].get();
		}
		return nullptr;
	}

	//---

	TextureT* const getTexture(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->textures.size())
				return doc->root->textures[id].get();
		}
		return nullptr;
	}

	//---

	SkinT* const getSkin(const Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->skins.size())
				return doc->root->skins[id].get();
		}
		return nullptr;
	}

	//---


	///-----------------------------------------------------------------------
	/// get-by-name
	/// note that names are optional and this might not work
	///-----------------------------------------------------------------------

	AccessorT* const getAccessor(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->accessors.begin(), doc->root->accessors.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->accessors.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	AnimationT* const getAnimation(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->animations.begin(), doc->root->animations.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->animations.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	BufferT* const getBuffer(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->buffers.begin(), doc->root->buffers.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->buffers.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	BufferViewT* const getBufferView(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->bufferViews.begin(), doc->root->bufferViews.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->bufferViews.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	CameraT* const getCamera(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->cameras.begin(), doc->root->cameras.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->cameras.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	ImageT* const getImage(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->images.begin(), doc->root->images.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->images.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	MaterialT* const getMaterial(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->materials.begin(), doc->root->materials.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->materials.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	// MeshPrimitiveT *const getMeshPrimitive(const Document* const doc, const char* name)
	//{
	//	if (doc && doc->root)
	//	{
	//		auto it = std::find_if(doc->root->meshprimitives.begin(), doc->root->meshprimitives.end(), [&name](auto&
	// elem) { 			return elem && elem->name == name;
	//		});
	//		if (it != doc->root->meshprimitives.end())
	//		{
	//			return it->get();
	//		}
	//	}
	//	return nullptr;
	//}

	//---

	MeshT* const getMesh(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->meshes.begin(), doc->root->meshes.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->meshes.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	NodeT* const getNode(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->nodes.begin(), doc->root->nodes.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->nodes.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	SceneT* const getScene(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->scenes.begin(), doc->root->scenes.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->scenes.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	SamplerT* const getSampler(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->samplers.begin(), doc->root->samplers.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->samplers.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	TextureT* const getTexture(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->textures.begin(), doc->root->textures.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->textures.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	SkinT* const getSkin(const Document* const doc, const char* name)
	{
		if (doc && doc->root)
		{
			auto it = std::find_if(doc->root->skins.begin(), doc->root->skins.end(), [&name](auto& elem) {
				return elem && elem->name == name;
			});
			if (it != doc->root->skins.end())
			{
				return it->get();
			}
		}
		return nullptr;
	}

	//---

	///-----------------------------------------------------------------------
	/// set-transform for nodes
	///-----------------------------------------------------------------------

	void setNodeMatrix(NodeT* const node, const mat4_t& m)
	{
		if (node)
		{
			auto msize = m.length() * mat4_t::col_type::length();
			node->matrix.reserve(msize);
			std::copy_n(&m[0][0], msize, std::back_inserter(node->matrix));

			node->rotation.clear();
			node->scale.clear();
			node->translation.clear();
		}
	}

	//---

	void setNodeRotation(NodeT* const node, const quat_t& q)
	{
		if (node)
		{
			node->rotation.reserve(q.length());
			std::copy_n(&q.x, q.length(), std::back_inserter(node->rotation));

			node->matrix.clear();
		}
	}

	//---

	void setNodeScale(NodeT* const node, const vec3_t& v)
	{
		if (node)
		{
			node->scale.reserve(v.length());
			std::copy_n(&v.x, v.length(), std::back_inserter(node->scale));

			node->matrix.clear();
		}
	}

	//---

	void setNodeTranslation(NodeT* const node, const vec3_t& v)
	{
		if (node)
		{
			node->translation.reserve(v.length());
			std::copy_n(&v.x, v.length(), std::back_inserter(node->translation));

			node->matrix.clear();
		}
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
