#ifndef STOKES_MAYA_API_HPP
#define STOKES_MAYA_API_HPP

#include <Stokes/Core/API.hpp>

#ifdef _WIN32
#ifdef STOKES_MAYA_BUILDING
#define STOKES_MAYA_API __declspec(dllexport)
#else
#define STOKES_MAYA_API __declspec(dllimport)
#endif
#else
#define STOKES_MAYA_API __attribute__ ((visibility ("default")))
#endif

#ifndef STOKES_MAYA_NAMESPACE
#define ENTER_NAMESPACE_STOKES_MAYA namespace Stokes { namespace Maya {
#define LEAVE_NAMESPACE_STOKES_MAYA } }
#endif

#endif
