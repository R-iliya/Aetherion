#pragma once

#include "core.h"

#if defined(_WIN32) && !defined(AETHERION_NO_CUSTOM_CRT) && !defined __clang__
	#define _INC_FLOAT // if float.h is imported after this file, MCW_EM is redefined
	#define AETHERION_CRT_API AETHERION_LIBRARY_IMPORT
	#ifndef MCW_EM
		#define _EM_OVERFLOW	0x00000004
		#define _EM_ZERODIVIDE	0x00000008
		#define _EM_INVALID		0x00000010
		#define _EM_DENORMAL	0x00080000
		#define MCW_EM			0x0008001f
	#endif
	#define DBL_MAX			1.7976931348623158e+308
	#define DBL_MIN			2.2250738585072014e-308
	#define FLT_MAX			3.402823466e+38F
	#define FLT_MIN			1.175494351e-38F
	#define NULL			0
	#define PRId64			"lld"
	#define PRIx64			"llx"

	extern "C" {
		typedef char* va_list;
		
		AETHERION_CRT_API void* __cdecl _aligned_malloc(size_t size, size_t align);
		AETHERION_CRT_API void __cdecl _aligned_free(void* ptr);
		AETHERION_CRT_API void* __cdecl _aligned_realloc(void* ptr, size_t size, size_t align);
		AETHERION_CRT_API void* __cdecl malloc(size_t size);
		AETHERION_CRT_API void __cdecl free(void* ptr);
		int __cdecl memcmp(const void* buf1, const void* buf2, size_t size);
		void* __cdecl memcpy(void* dst, void const* src, size_t size); __pragma(intrinsic(memcpy))
		void* __cdecl memmove(void* dst, const void* src, size_t size); __pragma(intrinsic(memmove))
		void* __cdecl memset(void*  dst, int val, size_t size); __pragma(intrinsic(memset))
		
		AETHERION_CRT_API __declspec(noreturn) void __cdecl abort(void);
		AETHERION_CRT_API unsigned int __cdecl _control87(unsigned int value, unsigned int mask);
		
		AETHERION_CRT_API float __cdecl acosf(float x);
		AETHERION_CRT_API float __cdecl cosf(float x);
		AETHERION_CRT_API float __cdecl atan2f(float y, float x);
		AETHERION_CRT_API float __cdecl tanf(float x);
		AETHERION_CRT_API float __cdecl asinf(float x);
		AETHERION_CRT_API float __cdecl sinf(float x);
		
		AETHERION_CRT_API double __cdecl atof(const char* str);
		AETHERION_CRT_API double __cdecl ceil(double x);
		double __cdecl fabs(double x);
		AETHERION_CRT_API double __cdecl floor(double _X);
		#ifndef _INC_MATH
			#define _INC_MATH
			inline float __cdecl fabsf(float x) { return (float)fabs(x); }
			AETHERION_CRT_API float __cdecl floorf(float x);
			AETHERION_CRT_API float __cdecl ceilf(float x);
		#endif
		AETHERION_CRT_API float fmodf(float x, float y);
		AETHERION_CRT_API int __cdecl _finite(double x);
		inline int __cdecl isinf(double x) { return !_finite(x); }
		
		AETHERION_CRT_API float __cdecl sqrtf(float x);
		double __cdecl sqrt(double _X);
		double __cdecl log10(double x);
		AETHERION_CRT_API float __cdecl powf(float x, float y);
		double __cdecl pow(double x, double y); __pragma(intrinsic(pow))

		size_t __cdecl strlen(const char* str);
		int __cdecl strcmp(const char* str, const char* str2);
		char* strcpy(char* dest, const char* src);
		AETHERION_CRT_API int __cdecl strncmp(const char* str1, const char* str2, size_t max_count);
		const char* __cdecl strstr(const char* str, const char* substr);
	}
#elif defined(__linux__) || defined(__clang__)
	#include <float.h>
	#include <inttypes.h>
	#include <limits.h>
	#include <math.h>
	#include <stdlib.h>
	#include <string.h>
#endif