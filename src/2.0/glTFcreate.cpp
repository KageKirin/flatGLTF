#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"


namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	AnimationT* const createAnimation(Document* const doc, const char* name)
	{
		auto instance = Animation_t{new AnimationT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->animations.push_back(std::move(instance));
		return doc->root->animations.back().get();
	}

	//---

	CameraT* const createCamera(Document* const doc, const char* name)
	{
		auto instance = Camera_t{new CameraT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->cameras.push_back(std::move(instance));
		return doc->root->cameras.back().get();
	}

	//---

	ImageT* const createImage(Document* const doc, const char* name)
	{
		auto instance = Image_t{new ImageT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->images.push_back(std::move(instance));
		return doc->root->images.back().get();
	}

	//---

	MaterialT* const createMaterial(Document* const doc, const char* name)
	{
		auto instance = Material_t{new MaterialT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->materials.push_back(std::move(instance));
		return doc->root->materials.back().get();
	}

	//---

	MeshPrimitiveT* const createMeshPrimitive(MeshT* const mesh)
	{
		auto instance = MeshPrimitive_t{new MeshPrimitiveT};
		mesh->primitives.push_back(std::move(instance));
		return mesh->primitives.back().get();
	}

	//---

	MeshT* const createMesh(Document* const doc, const char* name)
	{
		auto instance = Mesh_t{new MeshT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->meshes.push_back(std::move(instance));
		return doc->root->meshes.back().get();
	}

	//---

	NodeT* const createNode(Document* const doc, const char* name)
	{
		auto instance = Node_t{new NodeT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->nodes.push_back(std::move(instance));
		return doc->root->nodes.back().get();
	}

	//---

	SceneT* const createScene(Document* const doc, const char* name)
	{
		auto instance = Scene_t{new SceneT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->scenes.push_back(std::move(instance));
		return doc->root->scenes.back().get();
	}

	//---

	SamplerT* const createSampler(Document* const doc, const char* name)
	{
		auto instance = Sampler_t{new SamplerT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->samplers.push_back(std::move(instance));
		return doc->root->samplers.back().get();
	}

	//---

	TextureT* const createTexture(Document* const doc, const char* name)
	{
		auto instance = Texture_t{new TextureT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->textures.push_back(std::move(instance));
		return doc->root->textures.back().get();
	}

	//---

	SkinT* const createSkin(Document* const doc, const char* name)
	{
		auto instance = Skin_t{new SkinT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->skins.push_back(std::move(instance));
		return doc->root->skins.back().get();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------
	// glTFmesh.cpp

	MeshPrimitiveT* const createMeshPrimitive(Document* const doc, MeshT* const mesh, AccessorT* const accessor, MaterialT* const material)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(mesh);
		KHUTILS_ASSERT_PTR(accessor);

		auto meshPrim	 = createMeshPrimitive(mesh);
		meshPrim->indices = getId(doc, accessor);
		meshPrim->mode	= MeshPrimitiveMode::TRIANGLES;

		if (material)
		{
			meshPrim->material = getId(doc, material);
		}

		return meshPrim;
	}

	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	// glTFnode.cpp

	NodeT* const createNode(Document* const doc, CameraT* const cam)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(cam);

		auto node = createNode(doc);
		KHUTILS_ASSERT_PTR(node);

		node->camera = getId(doc, cam);

		return node;
	}

	//---------------------------------------------------------------------

	NodeT* const createNode(Document* const doc, MeshT* const mesh)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(mesh);

		auto node = createNode(doc);
		KHUTILS_ASSERT_PTR(node);

		node->mesh = getId(doc, mesh);

		return node;
	}

	//---------------------------------------------------------------------

	NodeT* const createNode(Document* const doc, SkinT* const skin)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(skin);

		auto node = createNode(doc);
		KHUTILS_ASSERT_PTR(node);

		node->skin = getId(doc, skin);

		return node;
	}

	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	// glTFimage.cpp

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

	//---------------------------------------------------------------------

	TextureT* const createTexture(Document* const doc, ImageT* const image)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(image);

		auto tex = createTexture(doc, (image->uri + "tex").c_str());
		KHUTILS_ASSERT_PTR(tex);
		tex->source = getId(doc, image);

		return tex;
	}

	//---------------------------------------------------------------------

}	// namespace glTF_2_0
