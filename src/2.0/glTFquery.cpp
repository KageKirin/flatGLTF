#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	std::vector<AccessorT*> queryAccessors(const Document* const doc, AccessorQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<AccessorT*> results;
		results.reserve(doc->root->accessors.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->accessors)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<AnimationT*> queryAnimations(const Document* const doc, AnimationQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<AnimationT*> results;
		results.reserve(doc->root->animations.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->animations)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<BufferT*> queryBuffers(const Document* const doc, BufferQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<BufferT*> results;
		results.reserve(doc->root->buffers.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->buffers)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<BufferViewT*> queryBufferViews(const Document* const doc, BufferViewQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<BufferViewT*> results;
		results.reserve(doc->root->bufferViews.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->bufferViews)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<CameraT*> queryCameras(const Document* const doc, CameraQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<CameraT*> results;
		results.reserve(doc->root->cameras.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->cameras)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<ImageT*> queryImages(const Document* const doc, ImageQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<ImageT*> results;
		results.reserve(doc->root->images.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->images)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<MaterialT*> queryMaterials(const Document* const doc, MaterialQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<MaterialT*> results;
		results.reserve(doc->root->materials.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->materials)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<MeshT*> queryMeshs(const Document* const doc, MeshQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<MeshT*> results;
		results.reserve(doc->root->meshes.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->meshes)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<NodeT*> queryNodes(const Document* const doc, NodeQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<NodeT*> results;
		results.reserve(doc->root->nodes.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->nodes)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<SceneT*> queryScenes(const Document* const doc, SceneQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<SceneT*> results;
		results.reserve(doc->root->scenes.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->scenes)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<SamplerT*> querySamplers(const Document* const doc, SamplerQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<SamplerT*> results;
		results.reserve(doc->root->samplers.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->samplers)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<TextureT*> queryTextures(const Document* const doc, TextureQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<TextureT*> results;
		results.reserve(doc->root->textures.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->textures)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---

	std::vector<SkinT*> querySkins(const Document* const doc, SkinQuery_t query)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(query);

		std::vector<SkinT*> results;
		results.reserve(doc->root->skins.size());
		auto resIt = std::back_inserter(results);

		for (auto& elem : doc->root->skins)
		{
			if (query(doc, elem.get()))
			{
				*resIt++ = elem.get();
			}
		}

		return results;
	}

	//---


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
