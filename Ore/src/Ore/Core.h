#pragma once

#ifdef ORE_PLATFORM_WINDOWS
#if ORE_DYNAMIC_LINK
	#ifdef  ORE_BUILD_DLL
		#define API __declspec(dllexport)
	#else
		#define API __declspec(dllimport)
	#endif
#else
	#define API
#endif
#else 
	#error Invalid Platform!
#endif

#ifdef ORE_ENABLE_ASSERTS 
	#define ORE_ASSERT(x, ...) { if(!(x)) { ORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); __debugbreak(); }}
	#define ORE_CORE_ASSERT(x, ...) { if(!(x)) { ORE_ERROR("ASSERTION FAILED: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define ORE_ASSERT(x, ...)
	#define ORE_CORE_ASSERT(x, ...)
#endif

#define ORE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(X) (1 << X)