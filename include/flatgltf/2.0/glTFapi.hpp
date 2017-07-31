#ifndef FLATGLTF_2_0_API_H_INC
#define FLATGLTF_2_0_API_H_INC

#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFmath_types.hpp"
#include "flatgltf/common/glTFapiexports.h"

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

	struct Document;


	Document* const		  createDocument(const char* name);
	void				  destroyDocument(Document* const);
	std::vector<uint8_t>& createBindata(Document* const, const char* name);

	std::vector<uint8_t>& getBindata(Document* const, const char* name);
	size_t				  setBindata(const std::vector<uint8_t>&, Document* const, const char* name);
	size_t				  addBindata(const std::vector<uint8_t>&, Document* const, const char* name);


	size_t addBufferData(const uint8_t* const data, size_t length, Document* const, BufferT* const);
	size_t setBufferViewData(const uint8_t* const data, size_t length, Document* const, BufferViewT* const);


	///-----------------------------------------------------------------------
	/// instantiation
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if error

	AccessorT* const   createAccessor(Document* const, const char* name = nullptr);
	AnimationT* const  createAnimation(Document* const, const char* name = nullptr);
	BufferT* const	 createBuffer(Document* const, const char* name = nullptr);
	BufferViewT* const createBufferView(Document* const, const char* name = nullptr);
	CameraT* const	 createCamera(Document* const, const char* name = nullptr);
	ImageT* const	  createImage(Document* const, const char* name = nullptr);
	MaterialT* const   createMaterial(Document* const, const char* name = nullptr);
	MeshT* const	   createMesh(Document* const, const char* name = nullptr);
	NodeT* const	   createNode(Document* const, const char* name = nullptr);
	SceneT* const	  createScene(Document* const, const char* name = nullptr);
	SamplerT* const	createSampler(Document* const, const char* name = nullptr);
	TextureT* const	createTexture(Document* const, const char* name = nullptr);
	SkinT* const	   createSkin(Document* const, const char* name = nullptr);

	MeshPrimitiveT* const createMeshPrimitive(MeshT* const);

	///-----------------------------------------------------------------------
	/// extended instantiation
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if error

	//! create buffer
	// if uri is null, data will be internal/base64 embedded
	BufferT* const createBuffer(Document* const, const char* uri, const char* name);

	//! create buffer view
	// data will be appended to buffer
	// buffer must exist
	BufferViewT* const createBufferView(const uint8_t* const data,	//
										size_t				 length,
										Document* const		 doc,
										BufferT* const		 buf,
										const char*			 name = nullptr);
	BufferViewT* const createBufferView(const std::vector<uint8_t>& data, Document* const doc, BufferT* const buf, const char* name = nullptr);

	//! create accessor on data in buffer
	// data will be appended to buffer
	// corresponding buffer view will be created as well
	AccessorT* const createAccessor(const uint8_t* const data, size_t length, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<uint8_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<mat4_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<mat3_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<mat2_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<vec4_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<vec3_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<vec2_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<i16vec4_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i16vec3_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i16vec2_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<i8vec4_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i8vec3_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i8vec2_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<u16vec4_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u16vec3_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u16vec2_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<u8vec4_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u8vec3_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u8vec2_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<int32_t>& data, Document* const, BufferT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<uint32_t>& data, Document* const, BufferT* const, const char* name = nullptr);

	//! create accessor on data in bufferView
	// data will be appended to bufferView->buffer
	// bufferView will be updated accordingly
	AccessorT* const createAccessor(const uint8_t* const data, size_t length, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<uint8_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<mat4_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<mat3_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<mat2_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<vec4_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<vec3_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<vec2_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<i16vec4_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i16vec3_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i16vec2_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<i8vec4_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i8vec3_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<i8vec2_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<u16vec4_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u16vec3_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u16vec2_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<u8vec4_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u8vec3_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<u8vec2_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);

	AccessorT* const createAccessor(const std::vector<int32_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);
	AccessorT* const createAccessor(const std::vector<uint32_t>& data, Document* const, BufferViewT* const, const char* name = nullptr);


	//! create a sampler with Good Defaults settings
	SamplerT* const createSampler_withDefaults(Document* const);

	//! create a texture to access given image
	// creates sampler for access
	TextureT* const createTexture(Document* const, ImageT* const);


	//! create meshprimitive
	// create meshprimitives and add them to given mesh
	MeshPrimitiveT* const createMeshPrimitive(Document* const, MeshT* const, AccessorT* const, MaterialT* const = nullptr);

	//! create camera node
	NodeT* const createNode(Document* const, CameraT* const);

	//! create mesh node
	NodeT* const createNode(Document* const, MeshT* const);

	//! create skin node
	NodeT* const createNode(Document* const, SkinT* const);

	///-----------------------------------------------------------------------
	/// simple get for unique elements
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found

	AssetT* const getAsset(const Document* const);	// has no name
	SceneT* const getScene(const Document* const);	// return scene if set, nullptr else

	///-----------------------------------------------------------------------
	/// get-by-id
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found
	AccessorT* const   getAccessor(const Document* const, glTFid_t);
	AnimationT* const  getAnimation(const Document* const, glTFid_t);
	BufferT* const	 getBuffer(const Document* const, glTFid_t);
	BufferViewT* const getBufferView(const Document* const, glTFid_t);
	CameraT* const	 getCamera(const Document* const, glTFid_t);
	ImageT* const	  getImage(const Document* const, glTFid_t);
	MaterialT* const   getMaterial(const Document* const, glTFid_t);
	MeshT* const	   getMesh(const Document* const, glTFid_t);
	NodeT* const	   getNode(const Document* const, glTFid_t);
	SceneT* const	  getScene(const Document* const, glTFid_t);
	SamplerT* const	getSampler(const Document* const, glTFid_t);
	TextureT* const	getTexture(const Document* const, glTFid_t);
	SkinT* const	   getSkin(const Document* const, glTFid_t);

	MeshPrimitiveT* const getMeshPrimitive(const MeshT* const, glTFid_t);

	///-----------------------------------------------------------------------
	/// get-by-name
	/// note that names are optional and this might not work
	///-----------------------------------------------------------------------
	// all functions return a const-pointer to mutable-object
	// nullptr if not found
	// CAVEAT: names are optional, so this might not work
	AccessorT* const   getAccessor(const Document* const, const char* name);
	AnimationT* const  getAnimation(const Document* const, const char* name);
	BufferT* const	 getBuffer(const Document* const, const char* name);
	BufferViewT* const getBufferView(const Document* const, const char* name);
	CameraT* const	 getCamera(const Document* const, const char* name);
	ImageT* const	  getImage(const Document* const, const char* name);
	MaterialT* const   getMaterial(const Document* const, const char* name);
	MeshT* const	   getMesh(const Document* const, const char* name);
	NodeT* const	   getNode(const Document* const, const char* name);
	SceneT* const	  getScene(const Document* const, const char* name);
	SamplerT* const	getSampler(const Document* const, const char* name);
	TextureT* const	getTexture(const Document* const, const char* name);
	SkinT* const	   getSkin(const Document* const, const char* name);

	///-----------------------------------------------------------------------
	/// get-id
	///-----------------------------------------------------------------------
	// all functions return a glTFid_t >= 0 if found, < 0 if not
	glTFid_t getId(const Document* const, const AccessorT* const);
	glTFid_t getId(const Document* const, const AnimationT* const);
	glTFid_t getId(const Document* const, const BufferT* const);
	glTFid_t getId(const Document* const, const BufferViewT* const);
	glTFid_t getId(const Document* const, const CameraT* const);
	glTFid_t getId(const Document* const, const ImageT* const);
	glTFid_t getId(const Document* const, const MaterialT* const);
	glTFid_t getId(const Document* const, const MeshPrimitiveT* const);
	glTFid_t getId(const Document* const, const MeshT* const);
	glTFid_t getId(const Document* const, const NodeT* const);
	glTFid_t getId(const Document* const, const SceneT* const);
	glTFid_t getId(const Document* const, const SamplerT* const);
	glTFid_t getId(const Document* const, const TextureT* const);
	glTFid_t getId(const Document* const, const SkinT* const);

	///-----------------------------------------------------------------------
	/// set-transform for nodes
	///-----------------------------------------------------------------------
	//! CAVEAT: matrix and RST are MUTUALLY exclusive
	//! to reflect this property, the other one WILL GET RESET when called
	void setNodeMatrix(NodeT* const, const mat4_t&);
	void setNodeRotation(NodeT* const, const quat_t&);
	void setNodeScale(NodeT* const, const vec3_t&);
	void setNodeTranslation(NodeT* const, const vec3_t&);

	///-----------------------------------------------------------------------
	///-----------------------------------------------------------------------

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_API_H_INC