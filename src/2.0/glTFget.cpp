#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/common/glTF_utils.h"
#include "glTF_internal_types.h"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

#include <algorithm>
#include <vector>

namespace glTF_2_0
{
	using namespace glTF_common;

	///-----------------------------------------------------------------------
	/// bindata
	///-----------------------------------------------------------------------

	std::vector<uint8_t>& get_Bindata(glTF_Document* const doc, const char* name)
	{
		return doc->bindata[name];
	}

	size_t set_Bindata(const std::vector<uint8_t>& data, glTF_Document* const doc, const char* name)
	{
		doc->bindata[name].clear();
		doc->bindata[name].reserve(data.size());
		std::copy(data.begin(), data.end(), std::back_inserter(doc->bindata[name]));
		return doc->bindata[name].size();
	}

	size_t add_Bindata(const std::vector<uint8_t>& data, glTF_Document* const doc, const char* name)
	{
		doc->bindata[name].reserve(doc->bindata[name].size() + data.size());
		std::copy(data.begin(), data.end(), std::back_inserter(doc->bindata[name]));
		return doc->bindata[name].size();
	}


	size_t add_BufferData(const uint8_t* const data, size_t length, glTF_Document* const doc, BufferT* const buf)
	{
		KHUTILS_ASSERT_PTR(data);
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(buf);

		if (is_DataUri(buf->uri))
		{
			auto bufData = convert_UriToData(buf->uri);
			std::copy_n(data, length, std::back_inserter(bufData));
			buf->uri		= convert_DataToUri(bufData);
			buf->byteLength = bufData.size();
		}
		else
		{
			auto& bufData = get_Bindata(doc, buf->uri.c_str());
			std::copy_n(data, length, std::back_inserter(bufData));
			buf->byteLength = bufData.size();
		}
		return buf->byteLength;
	}


	size_t set_BufferViewData(const uint8_t* const data, size_t length, glTF_Document* const doc, BufferViewT* const view)
	{
		KHUTILS_ASSERT_PTR(data);
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(view);
		KHUTILS_ASSERT_LESSEREQ(view->byteLength, 0);

		auto buf = get_Buffer(doc, view->buffer);
		KHUTILS_ASSERT_PTR(buf);

		view->byteOffset = buf->byteLength;
		add_BufferData(data, length, doc, buf);

		view->byteLength = length;
		view->byteStride = 0;
		view->target	 = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return view->byteLength;
	}


	///-----------------------------------------------------------------------
	/// simple get for unique elements
	///-----------------------------------------------------------------------

	AssetT* const get_Asset(const glTF_Document* const doc)
	{
		return (doc && doc->root) ? doc->root->asset.get() : nullptr;
	}

	SceneT* const get_Scene(const glTF_Document* const doc)
	{
		return (doc && doc->root) ? get_Scene(doc, doc->root->scene) : nullptr;
	}

	///-----------------------------------------------------------------------
	/// get-by-id
	///-----------------------------------------------------------------------

	AccessorT* const get_Accessor(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->accessors.size())
				return doc->root->accessors[id].get();
		}
		return nullptr;
	}

	//---

	AnimationT* const get_Animation(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->animations.size())
				return doc->root->animations[id].get();
		}
		return nullptr;
	}

	//---

	BufferT* const get_Buffer(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->buffers.size())
				return doc->root->buffers[id].get();
		}
		return nullptr;
	}

	//---

	BufferViewT* const get_BufferView(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->bufferViews.size())
				return doc->root->bufferViews[id].get();
		}
		return nullptr;
	}

	//---

	CameraT* const get_Camera(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->cameras.size())
				return doc->root->cameras[id].get();
		}
		return nullptr;
	}

	//---

	ImageT* const get_Image(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->images.size())
				return doc->root->images[id].get();
		}
		return nullptr;
	}

	//---

	MaterialT* const get_Material(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->materials.size())
				return doc->root->materials[id].get();
		}
		return nullptr;
	}

	//---

	// MeshPrimitiveT *const get_MeshPrimitive(const glTF_Document* const doc, glTFid_t id)
	//{
	//	if (doc && doc->root)
	//	{
	//		if (id >= 0 && id < doc->root->meshprimitives.size())
	//			return doc->root->meshprimitives[id].get();
	//	}
	//	return nullptr;
	//}

	//---

	MeshT* const get_Mesh(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->meshes.size())
				return doc->root->meshes[id].get();
		}
		return nullptr;
	}

	//---

	NodeT* const get_Node(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->nodes.size())
				return doc->root->nodes[id].get();
		}
		return nullptr;
	}

	//---

	SceneT* const get_Scene(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->scenes.size())
				return doc->root->scenes[id].get();
		}
		return nullptr;
	}

	//---

	SamplerT* const get_Sampler(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->samplers.size())
				return doc->root->samplers[id].get();
		}
		return nullptr;
	}

	//---

	TextureT* const get_Texture(const glTF_Document* const doc, glTFid_t id)
	{
		if (doc && doc->root)
		{
			if (id >= 0 && id < doc->root->textures.size())
				return doc->root->textures[id].get();
		}
		return nullptr;
	}

	//---

	SkinT* const get_Skin(const glTF_Document* const doc, glTFid_t id)
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

	AccessorT* const get_Accessor(const glTF_Document* const doc, const char* name)
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

	AnimationT* const get_Animation(const glTF_Document* const doc, const char* name)
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

	BufferT* const get_Buffer(const glTF_Document* const doc, const char* name)
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

	BufferViewT* const get_BufferView(const glTF_Document* const doc, const char* name)
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

	CameraT* const get_Camera(const glTF_Document* const doc, const char* name)
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

	ImageT* const get_Image(const glTF_Document* const doc, const char* name)
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

	MaterialT* const get_Material(const glTF_Document* const doc, const char* name)
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

	// MeshPrimitiveT *const get_MeshPrimitive(const glTF_Document* const doc, const char* name)
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

	MeshT* const get_Mesh(const glTF_Document* const doc, const char* name)
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

	NodeT* const get_Node(const glTF_Document* const doc, const char* name)
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

	SceneT* const get_Scene(const glTF_Document* const doc, const char* name)
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

	SamplerT* const get_Sampler(const glTF_Document* const doc, const char* name)
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

	TextureT* const get_Texture(const glTF_Document* const doc, const char* name)
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

	SkinT* const get_Skin(const glTF_Document* const doc, const char* name)
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

	void set_NodeMatrix(NodeT* const node, const mat4_t& m)
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

	void set_NodeRotation(NodeT* const node, const quat_t& q)
	{
		if (node)
		{
			node->rotation.reserve(q.length());
			std::copy_n(&q.x, q.length(), std::back_inserter(node->rotation));

			node->matrix.clear();
		}
	}

	//---

	void set_NodeScale(NodeT* const node, const vec3_t& v)
	{
		if (node)
		{
			node->scale.reserve(v.length());
			std::copy_n(&v.x, v.length(), std::back_inserter(node->scale));

			node->matrix.clear();
		}
	}

	//---

	void set_NodeTranslation(NodeT* const node, const vec3_t& v)
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
