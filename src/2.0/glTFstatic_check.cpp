#include "flatgltf/2.0/glTF_generated.h"

#include <GL/glew.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif	// defined(__APPLE__)


static_assert(static_cast<int32_t>(glTF_2_0::ComponentType::BYTE) == GL_BYTE, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::ComponentType::UNSIGNED_BYTE) == GL_UNSIGNED_BYTE, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::ComponentType::SHORT) == GL_SHORT, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::ComponentType::UNSIGNED_SHORT) == GL_UNSIGNED_SHORT, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::ComponentType::UNSIGNED_INT) == GL_UNSIGNED_INT, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::ComponentType::FLOAT) == GL_FLOAT, "enum value mismatch");


static_assert(static_cast<int32_t>(glTF_2_0::BufferViewTarget::ARRAY_BUFFER) == GL_ARRAY_BUFFER, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::BufferViewTarget::ELEMENT_ARRAY_BUFFER) == GL_ELEMENT_ARRAY_BUFFER,
			  "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::BufferViewTarget::UNIFORM_BUFFER) == GL_UNIFORM_BUFFER,
			  "enum value mismatch");


static_assert(static_cast<int32_t>(glTF_2_0::SamplerFilter::NEAREST) == GL_NEAREST, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::SamplerFilter::LINEAR) == GL_LINEAR, "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::SamplerFilter::NEAREST_MIPMAP_NEAREST) == GL_NEAREST_MIPMAP_NEAREST,
			  "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::SamplerFilter::LINEAR_MIPMAP_NEAREST) == GL_LINEAR_MIPMAP_NEAREST,
			  "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::SamplerFilter::NEAREST_MIPMAP_LINEAR) == GL_NEAREST_MIPMAP_LINEAR,
			  "enum value mismatch");
static_assert(static_cast<int32_t>(glTF_2_0::SamplerFilter::LINEAR_MIPMAP_LINEAR) == GL_LINEAR_MIPMAP_LINEAR,
			  "enum value mismatch");

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
