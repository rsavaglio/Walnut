#pragma once

#ifdef WN_PLATFORM_WINDOWS
	#ifdef WN_BUILD_DLL
		#define WALNUT_API __declspec(dllexport)
	#else
		#define WALNUT_API __declspec(dllimport)
	#endif
#else 
	#error Walnut only supports Windows!
#endif


#define BIT(x) (1 << x)