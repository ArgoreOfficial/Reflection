#pragma once

#include "cReflectedFunction.h"
#include "cReflectionRegistry.h"

// MACRO

#define FUNC_NAME_STR( _name ) #_name

#define REFLECT_STATIC( _f ) \
static cReflectedFunction func_##_f( _f ); \
static int id_##_f = cReflectionRegistry::registerReflection( #_f, __FILE__, __LINE__, (iArgOperator*)&( func_##_f ) );

#define REFLECT_STATIC_MEMBER( _c, _f ) \
static cReflectedFunction func_##_c ##_##_f( _c::_f ); \
static int id_##_c ##_##_f = cReflectionRegistry::registerReflection( FUNC_NAME_STR( _c::_f ), __FILE__, __LINE__, (iArgOperator*)&( func_ ##_c ##_ ##_f ) );
