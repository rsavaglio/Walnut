#pragma once

#ifdef WN_PLATFORM_WINDOWS
#if WN_DYNAMIC_LINK
	#ifdef WN_BUILD_DLL
		#define WALNUT_API __declspec(dllexport)
	#else
		#define WALNUT_API __declspec(dllimport)
	#endif
#else
	#define WALNUT_API
#endif
#else 
	#error Walnut only supports Windows!
#endif

#ifdef WN_DEBUG
	#define WN_ENABLE_ASSERTS
#endif

#ifdef WN_ENABLE_ASSERTS
	#define WN_ASSERT(x, ...) {if(!(x)) {WN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define WN_CORE_ASSERT(x, ...) {if(!(x)) {WN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define WN_ASSERT(x, ...)
	#define WN_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define WN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)