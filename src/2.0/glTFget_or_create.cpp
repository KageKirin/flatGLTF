#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	AccessorT* const getOrCreateAccessor(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getAccessor(doc, name);
		if (!elem)
		{
			elem = createAccessor(doc, name);
		}
		return elem;
	}

	//---

	AnimationT* const getOrCreateAnimation(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getAnimation(doc, name);
		if (!elem)
		{
			elem = createAnimation(doc, name);
		}
		return elem;
	}

	//---

	BufferT* const getOrCreateBuffer(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getBuffer(doc, name);
		if (!elem)
		{
			elem = createBuffer(doc, name);
		}
		return elem;
	}

	//---

	BufferViewT* const getOrCreateBufferView(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getBufferView(doc, name);
		if (!elem)
		{
			elem = createBufferView(doc, name);
		}
		return elem;
	}

	//---

	CameraT* const getOrCreateCamera(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getCamera(doc, name);
		if (!elem)
		{
			elem = createCamera(doc, name);
		}
		return elem;
	}

	//---

	ImageT* const getOrCreateImage(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getImage(doc, name);
		if (!elem)
		{
			elem = createImage(doc, name);
		}
		return elem;
	}

	//---

	MaterialT* const getOrCreateMaterial(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getMaterial(doc, name);
		if (!elem)
		{
			elem = createMaterial(doc, name);
		}
		return elem;
	}

	//---

	MeshT* const getOrCreateMesh(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getMesh(doc, name);
		if (!elem)
		{
			elem = createMesh(doc, name);
		}
		return elem;
	}

	//---

	NodeT* const getOrCreateNode(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getNode(doc, name);
		if (!elem)
		{
			elem = createNode(doc, name);
		}
		return elem;
	}

	//---

	SceneT* const getOrCreateScene(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getScene(doc, name);
		if (!elem)
		{
			elem = createScene(doc, name);
		}
		return elem;
	}

	//---

	SamplerT* const getOrCreateSampler(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getSampler(doc, name);
		if (!elem)
		{
			elem = createSampler(doc, name);
		}
		return elem;
	}

	//---

	TextureT* const getOrCreateTexture(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getTexture(doc, name);
		if (!elem)
		{
			elem = createTexture(doc, name);
		}
		return elem;
	}

	//---

	SkinT* const getOrCreateSkin(Document* const doc, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);

		auto elem = getSkin(doc, name);
		if (!elem)
		{
			elem = createSkin(doc, name);
		}
		return elem;
	}

	//---


	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
