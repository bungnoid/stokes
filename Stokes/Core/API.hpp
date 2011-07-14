#ifndef API_HPP
#define API_HPP

#ifdef _MSC_VER
#define STOKES_PLATFORM_WINDOWS
#ifdef _M_X64
#define STOKES_ARCH_X64
#else
#define STOKES_ARCH_X86
#endif
#else
#ifdef __GNUC__
#define STOKES_PLATFORM_POSIX
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

#ifndef STOKES_NAMESPACE
#define ENTER_NAMESPACE_STOKES namespace Stokes {
#define LEAVE_NAMESPACE_STOKES }
#endif

#endif
