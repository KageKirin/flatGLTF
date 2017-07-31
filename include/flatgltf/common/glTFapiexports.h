#ifndef GLTF_API_EXPORTS_H_INC
#define GLTF_API_EXPORTS_H_INC

// Emscripten compilation
#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#define FLATGLTF_API EMSCRIPTEN_KEEPALIVE
#define FLATGLTF_DLL_FUNC
#endif	// defined(__EMSCRIPTEN__)


// VS compilation
#if defined(_MSC_VER)
#ifndef FLATGLTF_API
#define FLATGLTF_API __cdecl
#endif	// !FLATGLTF_API
#ifndef FLATGLTF_DLL_FUNC
#if defined(FLATGLTF_BUILD_DLL)
#define FLATGLTF_DLL_FUNC __declspec(dllexport)
#elif defined(FLATGLTF_USE_DLL)
#define FLATGLTF_DLL_FUNC __declspec(dllimport)
#else
#define FLATGLTF_DLL_FUNC
#endif	// defined(FLATGLTF_BUILD_DLL) || defined(FLATGLTF_USE_DLL)
#endif	// !FLATGLTF_DLL_FUNC
#endif	// defined(_MSC_VER)


// GCC compilation //TODO expand for clang
#if defined(__GNUC__)
#ifndef FLATGLTF_API
#define FLATGLTF_API __cdecl
#endif	// !FLATGLTF_API
#ifndef FLATGLTF_DLL_FUNC
#if defined(FLATGLTF_BUILD_DLL)
#define FLATGLTF_DLL_FUNC __attribute__((dllexport)) __attribute__((visibility("default")))
#elif defined(FLATGLTF_USE_DLL)
#define FLATGLTF_DLL_FUNC __attribute__((dllimport))
#else
#define FLATGLTF_DLL_FUNC
#endif	// defined(FLATGLTF_BUILD_DLL) || defined(FLATGLTF_USE_DLL)
#endif	// !FLATGLTF_DLL_FUNC
#endif	// defined(__GNUC__)


// Define empty macros for other cases
#ifndef FLATGLTF_API
#define FLATGLTF_API
#endif	// !FLATGLTF_API

#ifndef FLATGLTF_DLL_FUNC
#define FLATGLTF_DLL_FUNC
#endif	// !FLATGLTF_DLL_FUNC

#endif	// GLTF_API_EXPORTS_H_INC
