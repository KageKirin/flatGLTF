#ifndef FLATGLTF_2_0_MATH_TYPES_H_INC
#define FLATGLTF_2_0_MATH_TYPES_H_INC

#include "glTF_generated.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <cctype>
#include <vector>

namespace glTF_2_0
{

	//---
	// matrix types with fitting padding
	// maybe move to glTF_glm.h
	template <typename T, glm::precision P = glm::defaultp>
	using tmat2_t = glm::tmat2x4<T, P>;

	template <typename T, glm::precision P = glm::defaultp>
	using tmat3_t = glm::tmat3x4<T, P>;

	template <typename T, glm::precision P = glm::defaultp>
	using tmat4_t = glm::tmat4x4<T, P>;

	template <typename T, glm::precision P = glm::defaultp>
	using tvec2_t = glm::tvec2<T, P>;

	template <typename T, glm::precision P = glm::defaultp>
	using tvec3_t = glm::tvec3<T, P>;

	template <typename T, glm::precision P = glm::defaultp>
	using tvec4_t = glm::tvec4<T, P>;

	template <typename T, glm::precision P = glm::defaultp>
	using tquat_t = glm::tquat<T, P>;

	using mat2_t  = glm::mat2x4;
	using mat3_t  = glm::mat3x4;
	using mat4_t  = glm::mat4x4;
	using vec2_t  = glm::vec2;
	using vec3_t  = glm::vec3;
	using vec4_t  = glm::vec4;
	using quat_t  = glm::quat;
	using imat2_t = glm::tmat2x4<int>;
	using imat3_t = glm::tmat3x4<int>;
	using imat4_t = glm::tmat4x4<int>;
	using ivec2_t = glm::ivec2;
	using ivec3_t = glm::ivec3;
	using ivec4_t = glm::ivec4;


	//--
	template <typename T, glm::precision P = glm::defaultp>
	inline tmat2_t<T, P> glm_cast(const glm::tmat2x2<T, P>& m)
	{
		return tmat2_t<T, P>{
		  {m[0].x, m[0].y, 0, 0},	//
		  {m[1].x, m[1].y, 0, 0},
		};
	}

	template <typename T, glm::precision P = glm::defaultp>
	inline tmat3_t<T, P> glm_cast(const glm::tmat3x3<T, P>& m)
	{
		return tmat3_t<T, P>{
		  {m[0].x, m[0].y, m[0].z, 0},	//
		  {m[1].x, m[1].y, m[1].z, 0},
		  {m[2].x, m[2].y, m[2].z, 0},
		};
	}

	template <typename T, glm::precision P = glm::defaultp>
	inline tmat4_t<T, P> glm_cast(const glm::tmat4x4<T, P>& m)
	{
		return m;
	}

	template <typename T, glm::precision P = glm::defaultp>
	inline glm::tmat2x2<T, P> glm_cast(const tmat2_t<T, P>& m)
	{
		return glm::tmat2x2<T, P>{
		  {m[0].x, m[0].y},	//
		  {m[1].x, m[1].y},
		};
	}

	template <typename T, glm::precision P = glm::defaultp>
	inline glm::tmat3x3<T, P> glm_cast(const tmat3_t<T, P>& m)
	{
		return glm::tmat3x3<T, P>{
		  {m[0].x, m[0].y, m[0].z},	//
		  {m[1].x, m[1].y, m[1].z},
		  {m[2].x, m[2].y, m[2].z},
		};
	}

	// template <typename T, glm::precision P = glm::defaultp>
	// inline glm::tmat4x4<T, P> glm_cast(const tmat4_t<T, P>& m)
	//{
	//	return m;
	//}

}	// namespace glTF_2_0

#endif	// ! FLATGLTF_2_0_MATH_TYPES_H_INC
