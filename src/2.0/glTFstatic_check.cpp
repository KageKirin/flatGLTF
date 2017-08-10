#include "flatgltf/2.0/glTF_generated.h"
#include "flatgltf/2.0/glTFmath_types.hpp"

#include <GL/glew.h>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif	// defined(__APPLE__)

//-------------------------------------------------------------------------

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

static_assert(sizeof(glTF_2_0::vec4_t) == glTF_2_0::vec4_t::length() * sizeof(glTF_2_0::vec4_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::vec3_t) == glTF_2_0::vec3_t::length() * sizeof(glTF_2_0::vec3_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::vec2_t) == glTF_2_0::vec2_t::length() * sizeof(glTF_2_0::vec2_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::i16vec4_t) == glTF_2_0::i16vec4_t::length() * sizeof(glTF_2_0::i16vec4_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::i16vec3_t) == glTF_2_0::i16vec3_t::length() * sizeof(glTF_2_0::i16vec3_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::i16vec2_t) == glTF_2_0::i16vec2_t::length() * sizeof(glTF_2_0::i16vec2_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::i8vec4_t) == glTF_2_0::i8vec4_t::length() * sizeof(glTF_2_0::i8vec4_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::i8vec3_t) == glTF_2_0::i8vec3_t::length() * sizeof(glTF_2_0::i8vec3_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::i8vec2_t) == glTF_2_0::i8vec2_t::length() * sizeof(glTF_2_0::i8vec2_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::u16vec4_t) == glTF_2_0::u16vec4_t::length() * sizeof(glTF_2_0::u16vec4_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::u16vec3_t) == glTF_2_0::u16vec3_t::length() * sizeof(glTF_2_0::u16vec3_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::u16vec2_t) == glTF_2_0::u16vec2_t::length() * sizeof(glTF_2_0::u16vec2_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::u8vec4_t) == glTF_2_0::u8vec4_t::length() * sizeof(glTF_2_0::u8vec4_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::u8vec3_t) == glTF_2_0::u8vec3_t::length() * sizeof(glTF_2_0::u8vec3_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::u8vec2_t) == glTF_2_0::u8vec2_t::length() * sizeof(glTF_2_0::u8vec2_t::value_type),
			  "value type size mismatch");

static_assert(sizeof(glTF_2_0::mat4_t) == glTF_2_0::mat4_t::length() * sizeof(glTF_2_0::mat4_t::col_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::mat3_t) == glTF_2_0::mat3_t::length() * sizeof(glTF_2_0::mat3_t::col_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::mat2_t) == glTF_2_0::mat2_t::length() * sizeof(glTF_2_0::mat2_t::col_type),
			  "value type size mismatch");

static_assert(sizeof(glTF_2_0::mat4_t)
				== glTF_2_0::mat4_t::length() * glTF_2_0::mat4_t::col_type::length() * sizeof(glTF_2_0::mat4_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::mat3_t)
				== glTF_2_0::mat3_t::length() * glTF_2_0::mat3_t::col_type::length() * sizeof(glTF_2_0::mat3_t::value_type),
			  "value type size mismatch");
static_assert(sizeof(glTF_2_0::mat2_t)
				== glTF_2_0::mat2_t::length() * glTF_2_0::mat2_t::col_type::length() * sizeof(glTF_2_0::mat2_t::value_type),
			  "value type size mismatch");


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
