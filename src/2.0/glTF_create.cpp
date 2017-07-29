#include "flatgltf/2.0/glTF_api.h"
#include "flatgltf/2.0/glTF_generated.h"

#include "glTF_internal_types.h"

namespace glTF_2_0
{
	using namespace detail;

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	static AssetT* create_Asset_default(const char* name);

	glTF_Document* const create_Document(const char* name)
	{
		auto instance		  = std::unique_ptr<glTF_Document>{new glTF_Document};
		instance->root		  = Root_t{new RootT};
		instance->root->asset = Asset_t{create_Asset_default(name)};

		return instance.release();
	}

	//---

	void destroy_Document(glTF_Document* const doc)
	{
		if (doc)
		{
			delete doc;
		}
	}

	//---

	std::vector<uint8_t>& create_Bindata(glTF_Document* const doc, const char* name)
	{
		return doc->bindata[name];
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	static AssetT* create_Asset_default(const char* name)
	{
		auto instance		 = Asset_t{new AssetT};
		instance->name		 = name;
		instance->version	= "2.0";
		instance->minVersion = "2.0";
		instance->copyright  = "NONE, unless specified otherwise";
		instance->generator  = "flatgltf, unless specified otherwise";
		return instance.release();
	}

	//-------------------------------------------------------------------------
	//-------------------------------------------------------------------------

	AccessorT* const create_Accessor(glTF_Document* const doc, const char* name)
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

	AnimationT* const create_Animation(glTF_Document* const doc, const char* name)
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

	BufferT* const create_Buffer(glTF_Document* const doc, const char* name)
	{
		auto instance = Buffer_t{new BufferT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->buffers.push_back(std::move(instance));
		return doc->root->buffers.back().get();
	}

	//---

	BufferViewT* const create_BufferView(glTF_Document* const doc, const char* name)
	{
		auto instance = BufferView_t{new BufferViewT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->bufferViews.push_back(std::move(instance));
		return doc->root->bufferViews.back().get();
	}

	//---

	CameraT* const create_Camera(glTF_Document* const doc, const char* name)
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

	ImageT* const create_Image(glTF_Document* const doc, const char* name)
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

	MaterialT* const create_Material(glTF_Document* const doc, const char* name)
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

	MeshPrimitiveT* const create_MeshPrimitive(MeshT* const mesh)
	{
		auto instance = MeshPrimitive_t{new MeshPrimitiveT};
		mesh->primitives.push_back(std::move(instance));
		return mesh->primitives.back().get();
	}

	//---

	MeshT* const create_Mesh(glTF_Document* const doc, const char* name)
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

	NodeT* const create_Node(glTF_Document* const doc, const char* name)
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

	SceneT* const create_Scene(glTF_Document* const doc, const char* name)
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

	SamplerT* const create_Sampler(glTF_Document* const doc, const char* name)
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

	TextureT* const create_Texture(glTF_Document* const doc, const char* name)
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

	SkinT* const create_Skin(glTF_Document* const doc, const char* name)
	{
		auto instance = Skin_t{new SkinT};
		if (name)
		{
			instance->name = name;
		}
		doc->root->skins.push_back(std::move(instance));
		return doc->root->skins.back().get();
	}

//---


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

#ifdef EXTRAS
	//////////////////////////////////////////////////////////////////////////

	//! create buffer
	// if name is null, data will be internal
	BufferT* const create_Buffer(glTF_Document* const doc, const char* uri, const char* name)
	{
		auto buffer = create_Buffer(doc, name);
		if (uri)
		{
			create_Bindata(doc, uri);
		}
		else
		{
		}

		return buffer;
	}

	//////////////////////////////////////////////////////////////////////////

	BufferViewT* const create_BufferView(const uint8_t* const data, size_t length, glTF_Document* const doc, BufferT* const buf, const char* name)
	{
		KHUTILS_ASSERT_PTR(buf);

		auto view = create_BufferView(doc);
		KHUTILS_ASSERT_PTR(view);

		view->buffer = id_of(doc, buf);

		if (name)
		{
			view->name = name;
		}

		set_BufferViewData(data, length, doc, view);

		return view;
	}


	BufferViewT* const create_BufferView(const std::vector<uint8_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
	{
		return createBufferView(data.data(), data.size(), doc, buf);
	}

	//////////////////////////////////////////////////////////////////////////

	//! create accessor on data in buffer
	// data will be appended to buffer
	AccessorT* const create_Accessor(const uint8_t* const data, size_t length, glTF_Document* const doc, BufferT* const buf, const char* name)
	{
		auto view	 = createBufferView(data, length, doc, buf);
		auto accessor = create_Accessor(doc);
		KHUTILS_ASSERT_PTR(accessor);

		accessor->bufferView	= id_of(doc, view);
		accessor->byteOffset	= 0;
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= length;
		accessor->type			= AccessorType::SCALAR;
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<uint8_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name))
	{
		auto accessor = createAccessor(data.data(), data.size(), doc, buf);
		KHUTILS_ASSERT_PTR(accessor);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<vec4_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<vec3_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<vec2_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<int32_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name))
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ELEMENT_ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<uint32_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name))
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ELEMENT_ARRAY_BUFFER);
		return accessor;
	}

	//////////////////////////////////////////////////////////////////////////

	AccessorT* const create_Accessor(const std::vector<i16vec4_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i16vec3_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i16vec2_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i8vec4_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i8vec3_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i8vec2_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u16vec4_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u16vec3_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u16vec2_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u8vec4_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);

		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u8vec3_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u8vec2_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<mat4_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<mat3_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<mat2_t>& data, glTF_Document* const doc, BufferT* const buf, const char* name)
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

		auto bufferView = get_BufferView(doc, accessor->bufferView);
		KHUTILS_ASSERT_PTR(bufferView);
		bufferView->target = static_cast<int32_t>(BufferViewTarget::ARRAY_BUFFER);
		return accessor;
	}


	//////////////////////////////////////////////////////////////////////////

	//! create accessor on data in bufferView
	AccessorT* const create_Accessor(const uint8_t* const data, size_t length, glTF_Document* const doc, BufferViewT* const view, const char* name)
	{
		KHUTILS_ASSERT_PTR(doc);
		KHUTILS_ASSERT_PTR(view);
		auto view	 = add_BufferView(data, length, doc, view);
		auto accessor = create_Accessor(doc);
		KHUTILS_ASSERT_PTR(accessor);

		accessor->bufferView	= id_of(doc, view);
		accessor->byteOffset	= 0;
		accessor->componentType = static_cast<int32_t>(ComponentType::UNSIGNED_BYTE);
		accessor->normalized	= false;
		accessor->count			= length;
		accessor->type			= AccessorType::SCALAR;
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<uint8_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name))
	{
		auto accessor = createAccessor(data.data(), data.size(), doc, view);
		KHUTILS_ASSERT_PTR(accessor);
		return accessor;
	}

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<vec4_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<vec3_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<vec2_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<int32_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name))
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<uint32_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name))
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

	AccessorT* const create_Accessor(const std::vector<i16vec4_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i16vec3_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i16vec2_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i8vec4_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i8vec3_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<i8vec2_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u16vec4_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u16vec3_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u16vec2_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u8vec4_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u8vec3_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<u8vec2_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<mat4_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<mat3_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

	//---------------------------------------------------------------------

	AccessorT* const create_Accessor(const std::vector<mat2_t>& data, glTF_Document* const doc, BufferViewT* const view, const char* name)
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

//---------------------------------------------------------------------
#endif	// EXTRAS

}	// namespace glTF_2_0
