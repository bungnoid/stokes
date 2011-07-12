#ifndef STOKES_HPP
#define STOKES_HPP

#ifdef _MSC_VER
	#ifdef _M_X64
		#define STOKES_ARCH_X64
	#else
		#define STOKES_ARCH_X86
	#endif
#else
	#ifdef __GNUC__
		#if defined __x86_64 || defined __amd64
			#define STOKES_ARCH_X64
		#else
			#define STOKES_ARCH_X86
		#endif
	#endif
#endif

#ifdef _WIN32
	#ifdef STOKES_BUILD
		#define STOKES_API __declspec(dllexport)
	#else
		#define STOKES_API __declspec(dllimport)
	#endif
#else
	#define STOKES_API __attribute__ ((visibility ("default")))
#endif

#endif
