#ifndef STOKES_CORE_API_HPP
#define STOKES_CORE_API_HPP

#ifdef _WIN32
#ifdef STOKES_CORE_BUILDING
#define STOKES_CORE_API __declspec(dllexport)
#else
#define STOKES_CORE_API __declspec(dllimport)
#endif
#else
#define STOKES_CORE_API __attribute__ ((visibility ("default")))
#endif

#ifndef STOKES_NAMESPACE
#define ENTER_NAMESPACE_STOKES namespace Stokes {
#define LEAVE_NAMESPACE_STOKES }
#endif

#endif
