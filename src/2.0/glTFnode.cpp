#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	NodeT* const createNode(Document* const doc, CameraT* const cam)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(cam);

		auto node = createNode(doc);
		KHUTILS_ASSERT_PTR(node);

		node->camera = getId(doc, cam);

		return node;
	}

	//---

	NodeT* const createNode(Document* const doc, MeshT* const mesh)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(mesh);

		auto node = createNode(doc);
		KHUTILS_ASSERT_PTR(node);

		node->mesh = getId(doc, mesh);

		return node;
	}

	//---

	NodeT* const createNode(Document* const doc, SkinT* const skin)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(skin);

		auto node = createNode(doc);
		KHUTILS_ASSERT_PTR(node);

		node->skin = getId(doc, skin);

		return node;
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
			node->matrix.resize(msize);
			std::copy_n(&m[0][0], msize, node->matrix.begin());

			// reset RST
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
			node->rotation.resize(q.length());
			std::copy_n(&q.x, q.length(), node->rotation.begin());

			// reset matrix
			node->matrix.clear();
		}
	}

	//---

	void setNodeScale(NodeT* const node, const vec3_t& v)
	{
		if (node)
		{
			node->scale.resize(v.length());
			std::copy_n(&v.x, v.length(), node->scale.begin());

			// reset matrix
			node->matrix.clear();
		}
	}

	//---

	void setNodeTranslation(NodeT* const node, const vec3_t& v)
	{
		if (node)
		{
			node->translation.resize(v.length());
			std::copy_n(&v.x, v.length(), node->translation.begin());

			// reset matrix
			node->matrix.clear();
		}
	}

	//---

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
