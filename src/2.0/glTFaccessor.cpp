#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFapi.hpp"
#include "flatgltf/2.0/glTFmath_types.hpp"

#include "glTFinternal.hpp"

#define KHUTILS_ASSERTION_INLINE

#include "khutils/assertion.hpp"
#include "khutils/runtime_exceptions.hpp"

namespace glTF_2_0
{
	//-------------------------------------------------------------------------

	AccessorT* const createAccessor(Document* const doc, const char* name)
	{
		auto instance = Accessor_t{new AccessorT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->accessors.push_back(std::move(instance));
		return doc->root->accessors.back().get();
	}

	//---

	//! create accessor on data in buffer
	// data will be appended to buffer
	AccessorT* const createAccessor(const uint8_t* const data, size_t length, Document* const doc, BufferT* const buf, const char* name)
	{
		auto view	 = createBufferView(data, length, doc, buf);
		auto accessor = createAccessor(doc);
		KHUTILS_ASSERT_PTR(accessor);

		accessor->bufferView	= getId(doc, view);
		accessor->byteOffset	= 0;
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= length;
		accessor->type			= AccessorType::SCALAR;
		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<uint8_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(data.data(), data.size(), doc, buf);
		KHUTILS_ASSERT_PTR(accessor);
		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<vec4_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(vec4_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<vec3_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(vec3_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<vec2_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(vec2_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<int32_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(int32_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_INT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::SCALAR;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ELEMENT_ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<uint32_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(int32_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_INT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::SCALAR;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ELEMENT_ARRAY_BUFFER);

		return accessor;
	}

	//////////////////////////////////////////////////////////////////////////

	AccessorT* const createAccessor(const std::vector<i16vec4_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i16vec4_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i16vec3_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i16vec3_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i16vec2_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i16vec2_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i8vec4_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i8vec4_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i8vec3_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i8vec3_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i8vec2_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i8vec2_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u16vec4_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u16vec4_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u16vec3_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u16vec3_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u16vec2_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u16vec2_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u8vec4_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u8vec4_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u8vec3_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u8vec3_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u8vec2_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u8vec2_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		auto bufferView = getBufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<mat4_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(mat4_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::MAT4;

		// auto bufferView = getBufferView(doc, accessor->bufferView);
		// KHUTILS_ASSERT_PTR(bufferView);
		// bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<mat3_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(mat3_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::MAT3;

		// auto bufferView = getBufferView(doc, accessor->bufferView);
		// KHUTILS_ASSERT_PTR(bufferView);
		// bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<mat2_t>& data, Document* const doc, BufferT* const buf, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(mat2_t),
									   doc,
									   buf);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::MAT2;

		// auto bufferView = getBufferView(doc, accessor->bufferView);
		// KHUTILS_ASSERT_PTR(bufferView);
		// bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}


	//////////////////////////////////////////////////////////////////////////

	//! create accessor on data in bufferView
	AccessorT* const createAccessor(const uint8_t* const data, size_t length, Document* const doc, BufferViewT* const view, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(view);
		auto sz		  = setBufferViewData(data, length, doc, view);
		auto accessor = createAccessor(doc);
		KHUTILS_ASSERT_PTR(accessor);

		accessor->bufferView	= getId(doc, view);
		accessor->byteOffset	= 0;
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= length;
		accessor->type			= AccessorType::SCALAR;
		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<uint8_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(data.data(), data.size(), doc, view);
		KHUTILS_ASSERT_PTR(accessor);
		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<vec4_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(vec4_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<vec3_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(vec3_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<vec2_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(vec2_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<int32_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(int32_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_INT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::SCALAR;


		KHUTILS_ASSERT_PTR(view);
		view->target = static_cast<int32_t>(BufferViewTarget::ELEMENT_ARRAY_BUFFER);
		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<uint32_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(int32_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_INT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::SCALAR;


		KHUTILS_ASSERT_PTR(view);
		view->target = static_cast<int32_t>(BufferViewTarget::ELEMENT_ARRAY_BUFFER);
		return accessor;
	}

	//////////////////////////////////////////////////////////////////////////

	AccessorT* const createAccessor(const std::vector<i16vec4_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i16vec4_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i16vec3_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i16vec3_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i16vec2_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i16vec2_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i8vec4_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i8vec4_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i8vec3_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i8vec3_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<i8vec2_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(i8vec2_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u16vec4_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u16vec4_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u16vec3_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u16vec3_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u16vec2_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u16vec2_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_SHORT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u8vec4_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u8vec4_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC4;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u8vec3_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u8vec3_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC3;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<u8vec2_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(u8vec2_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::VEC2;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<mat4_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(mat4_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::MAT4;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<mat3_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(mat3_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::MAT3;

		return accessor;
	}

	//---

	AccessorT* const createAccessor(const std::vector<mat2_t>& data, Document* const doc, BufferViewT* const view, const char* name)
	{
		auto accessor = createAccessor(reinterpret_cast<const uint8_t* const>(data.data()),	//
									   data.size() * sizeof(mat2_t),
									   doc,
									   view);
		KHUTILS_ASSERT_PTR(accessor);
		accessor->componentType = static_cast<int32_t>(ComponentType::FLOAT);
		accessor->normalized	= false;
		accessor->count			= data.size();
		accessor->type			= AccessorType::MAT2;

		return accessor;
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

}	// namespace glTF_2_0
