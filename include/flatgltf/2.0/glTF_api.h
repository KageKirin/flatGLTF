#ifndef FLATGLTF_2_0_API_H_INC
#define FLATGLTF_2_0_API_H_INC

#include "../common/glTF_api_exports.h"
#include "glTF_generated.h"
#include "glTF_math_types.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace glTF_2_0
{
	///-----------------------------------------------------------------------
	/// id type alias
	///-----------------------------------------------------------------------

	using glTFid_t = int32_t;

	///-----------------------------------------------------------------------
	/// document structure (PIMPL)
	///-----------------------------------------------------------------------

	struct glTF_Document;


	glTF_Document* const  create_Document(const char* name);
	void				  destroy_Document(glTF_Document* const);
	std::vector<uint8_t>& create_Bindata(glTF_Document* const, const char* name);

	std::vector<uint8_t>& get_Bindata(glTF_Document* const, const char* name);
	size_t				  set_Bindata(const std::vector<uint8_t>&, glTF_Document* const, const char* name);
	size_t				  add_Bindata(const std::vector<uint8_t>&, glTF_Document* const, const char* name);


	size_t add_BufferData(const uint8_t* const data, size_t length, glTF_Document* const, BufferT* const);
	size_t set_BufferViewData(const uint8_t* const data, size_t length, glTF_Document* const, BufferViewT* const);

	///-----------------------------------------------------------------------
	/// instantiation
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if error


	AccessorT* const   create_Accessor(glTF_Document* const, const char* name = nullptr);
	AnimationT* const  create_Animation(glTF_Document* const, const char* name = nullptr);
	BufferT* const	 create_Buffer(glTF_Document* const, const char* name = nullptr);
	BufferViewT* const create_BufferView(glTF_Document* const, const char* name = nullptr);
	CameraT* const	 create_Camera(glTF_Document* const, const char* name = nullptr);
	ImageT* const	  create_Image(glTF_Document* const, const char* name = nullptr);
	MaterialT* const   create_Material(glTF_Document* const, const char* name = nullptr);
	MeshT* const	   create_Mesh(glTF_Document* const, const char* name = nullptr);
	NodeT* const	   create_Node(glTF_Document* const, const char* name = nullptr);
	SceneT* const	  create_Scene(glTF_Document* const, const char* name = nullptr);
	SamplerT* const	create_Sampler(glTF_Document* const, const char* name = nullptr);
	TextureT* const	create_Texture(glTF_Document* const, const char* name = nullptr);
	SkinT* const	   create_Skin(glTF_Document* const, const char* name = nullptr);

	MeshPrimitiveT* const create_MeshPrimitive(MeshT* const);

	///-----------------------------------------------------------------------
	/// simple get for unique elements
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found

	AssetT* const get_Asset(const glTF_Document* const);	// has no name
	SceneT* const get_Scene(const glTF_Document* const);	// return scene if set, nullptr else

	///-----------------------------------------------------------------------
	/// get-by-id
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found


	AccessorT* const   get_Accessor(const glTF_Document* const, glTFid_t);
	AnimationT* const  get_Animation(const glTF_Document* const, glTFid_t);
	BufferT* const	 get_Buffer(const glTF_Document* const, glTFid_t);
	BufferViewT* const get_BufferView(const glTF_Document* const, glTFid_t);
	CameraT* const	 get_Camera(const glTF_Document* const, glTFid_t);
	ImageT* const	  get_Image(const glTF_Document* const, glTFid_t);
	MaterialT* const   get_Material(const glTF_Document* const, glTFid_t);
	MeshT* const	   get_Mesh(const glTF_Document* const, glTFid_t);
	NodeT* const	   get_Node(const glTF_Document* const, glTFid_t);
	SceneT* const	  get_Scene(const glTF_Document* const, glTFid_t);
	SamplerT* const	get_Sampler(const glTF_Document* const, glTFid_t);
	TextureT* const	get_Texture(const glTF_Document* const, glTFid_t);
	SkinT* const	   get_Skin(const glTF_Document* const, glTFid_t);

	MeshPrimitiveT* const get_MeshPrimitive(const MeshT* const, glTFid_t);

	///-----------------------------------------------------------------------
	/// get-by-name
	/// note that names are optional and this might not work
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found
	// CAVEAT:

	AccessorT* const   get_Accessor(const glTF_Document* const, const char* name);
	AnimationT* const  get_Animation(const glTF_Document* const, const char* name);
	BufferT* const	 get_Buffer(const glTF_Document* const, const char* name);
	BufferViewT* const get_BufferView(const glTF_Document* const, const char* name);
	CameraT* const	 get_Camera(const glTF_Document* const, const char* name);
	ImageT* const	  get_Image(const glTF_Document* const, const char* name);
	MaterialT* const   get_Material(const glTF_Document* const, const char* name);
	MeshT* const	   get_Mesh(const glTF_Document* const, const char* name);
	NodeT* const	   get_Node(const glTF_Document* const, const char* name);
	SceneT* const	  get_Scene(const glTF_Document* const, const char* name);
	SamplerT* const	get_Sampler(const glTF_Document* const, const char* name);
	TextureT* const	get_Texture(const glTF_Document* const, const char* name);
	SkinT* const	   get_Skin(const glTF_Document* const, const char* name);

	///-----------------------------------------------------------------------
	/// get-id
	///-----------------------------------------------------------------------
	// all functions return a glTFid_t >= 0 if found, < 0 if not

	glTFid_t id_of(const glTF_Document* const, const AccessorT* const);
	glTFid_t id_of(const glTF_Document* const, const AnimationT* const);
	glTFid_t id_of(const glTF_Document* const, const BufferT* const);
	glTFid_t id_of(const glTF_Document* const, const BufferViewT* const);
	glTFid_t id_of(const glTF_Document* const, const CameraT* const);
	glTFid_t id_of(const glTF_Document* const, const ImageT* const);
	glTFid_t id_of(const glTF_Document* const, const MaterialT* const);
	glTFid_t id_of(const glTF_Document* const, const MeshPrimitiveT* const);
	glTFid_t id_of(const glTF_Document* const, const MeshT* const);
	glTFid_t id_of(const glTF_Document* const, const NodeT* const);
	glTFid_t id_of(const glTF_Document* const, const SceneT* const);
	glTFid_t id_of(const glTF_Document* const, const SamplerT* const);
	glTFid_t id_of(const glTF_Document* const, const TextureT* const);
	glTFid_t id_of(const glTF_Document* const, const SkinT* const);

	///-----------------------------------------------------------------------
	/// set-transform for nodes
	///-----------------------------------------------------------------------

	void set_NodeMatrix(NodeT* const, const mat4_t&);
	void set_NodeRotation(NodeT* const, const quat_t&);
	void set_NodeScale(NodeT* const, const vec3_t&);
	void set_NodeTranslation(NodeT* const, const vec3_t&);

	///-----------------------------------------------------------------------
	/// utility
	///-----------------------------------------------------------------------

	/// prepares glTF data for GLB serialization
	//- changes URIs
	//- merges all mapped bindata into a single blob
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API binarize_Document(glTF_Document* const);

	/// prepares glTF data for glTF-embedded format
	//- changes URIs to contain base64 encoded buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API embed_Document(glTF_Document* const);

	/// prepares glTF data for glTF-multi format
	//- changes URIs to reference external buffers
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API dislodge_Document(glTF_Document* const);

	/// prepares glTF data for glTF-multi format
	//- splits buffers into multiple buffers according to bufferViews
	//- changes bufferViews accordingly
	FLATGLTF_DLL_FUNC bool FLATGLTF_API split_Document(glTF_Document* const);

	///-----------------------------------------------------------------------
	/// file I/O
	///-----------------------------------------------------------------------

	// JSON file interface
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document(glTF_Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document(const glTF_Document* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document(glTF_Document* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document(const glTF_Document* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document(glTF_Document* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document(const glTF_Document* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document(glTF_Document* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document(const glTF_Document* const, std::vector<uint8_t>& buffer);

	// API to fill/dump bindata from glTF
	// file interface for external bindata resources
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_bindata(glTF_Document*);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_bindata(const glTF_Document*);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_bindata(std::vector<uint8_t>& bindata, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_bindata(const std::vector<uint8_t>& bindata, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_bindata(std::vector<uint8_t>& bindata, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_bindata(const std::vector<uint8_t>& bindata, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_bindata(std::vector<uint8_t>& buffer, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_bindata(const std::vector<uint8_t>& buffer, std::ostream&);

	// GLB file interface
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_binary(glTF_Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_binary(const glTF_Document* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_binary(glTF_Document* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_binary(const glTF_Document* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_binary(glTF_Document* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_binary(const glTF_Document* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_binary(glTF_Document* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_binary(const glTF_Document* const, std::vector<uint8_t>& buffer);

	// GLF file interface
	// GLF is a FlatGLTF original format, basically JSON dumped as flatbuffer
	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_flat(glTF_Document* const, const char* uri);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_flat(const glTF_Document* const, const char* uri);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_flat(glTF_Document* const, FILE* file);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_flat(const glTF_Document* const, FILE* file);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_flat(glTF_Document* const, std::istream&);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_flat(const glTF_Document* const, std::ostream&);

	FLATGLTF_DLL_FUNC bool FLATGLTF_API load_Document_flat(glTF_Document* const, const std::vector<uint8_t>& buffer);
	FLATGLTF_DLL_FUNC bool FLATGLTF_API save_Document_flat(const glTF_Document* const, std::vector<uint8_t>& buffer);

///-----------------------------------------------------------------------
///-----------------------------------------------------------------------

#ifdef EXTRAS
	//---------------------------------------------------------------------
	//! create buffer
	// if uri is null, data will be internal/base64 embedded
	BufferT* const create_Buffer(glTF_Document* const, const char* uri = nullptr, const char* name = nullptr);

	//---------------------------------------------------------------------
	//! create buffer view
	// data will be appended to buffer
	// buffer must exist
	BufferViewT* const create_BufferView(const uint8_t* const data,	//
										 size_t				  length,
										 glTF_Document* const doc,
										 BufferT* const		  buf,
										 const char*		  name = nullptr);
	BufferViewT* const create_BufferView(const std::vector<uint8_t>& data,
										 glTF_Document* const		 doc,
										 BufferT* const				 buf,
										 const char*				 name = nullptr);

	//---------------------------------------------------------------------
	//! create accessor on data in buffer
	// data will be appended to buffer
	// corresponding buffer view will be created as well
	AccessorT* const create_Accessor(const uint8_t* const data, size_t length, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<uint8_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<mat4_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<mat3_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<mat2_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<vec4_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<vec3_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<vec2_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<i16vec4_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i16vec3_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i16vec2_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<i8vec4_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i8vec3_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i8vec2_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<u16vec4_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u16vec3_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u16vec2_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<u8vec4_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u8vec3_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u8vec2_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<int32_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<uint32_t>& data, glTF_Document* const, BufferT* const, const char* name = nullptr);

	//---------------------------------------------------------------------
	//! create accessor on data in bufferView
	// data will be appended to bufferView->buffer
	// bufferView will be updated accordingly

	AccessorT* const create_Accessor(const uint8_t* const data, size_t length, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<uint8_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<mat4_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<mat3_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<mat2_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<vec4_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<vec3_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<vec2_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<i16vec4_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i16vec3_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i16vec2_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<i8vec4_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i8vec3_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<i8vec2_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<u16vec4_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u16vec3_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u16vec2_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<u8vec4_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u8vec3_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<u8vec2_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const create_Accessor(const std::vector<int32_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const create_Accessor(const std::vector<uint32_t>& data, glTF_Document* const, BufferViewT* const, const char* name = nullptr);

#endif	// EXTRAS

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_API_H_INC
