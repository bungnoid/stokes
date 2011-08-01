#ifndef STOKES_CORE_DATATYPE_HPP
#define STOKES_CORE_DATATYPE_HPP

#include <boost/shared_ptr.hpp>

#include <string>

#include <Stokes/Core/API.hpp>
#include <Stokes/Core/Platform.hpp>

ENTER_NAMESPACE_STOKES

typedef bool               Bool;

typedef int                Integer32;
typedef unsigned int       Integer32U;

typedef long long          Integer64;
typedef unsigned long long Integer64U;

typedef float              Float;
typedef double             Double;

typedef char               Char;
typedef wchar_t            WChar;
typedef std::string        CharString;
typedef std::wstring       WideString;

LEAVE_NAMESPACE_STOKES

#endif
