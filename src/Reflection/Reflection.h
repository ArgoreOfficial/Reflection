#pragma once

#include "cReflectedFunction.h"
#include "cReflectionRegistry.h"

// MACRO


#define REFLECT_STATIC( _f ) \
int cReflectionHelper<decltype( _f ), _f>::id{ cReflectionRegistry::reflectStatic( #_f, (iArgOperator*)&( cReflectionHelper<decltype( _f ), _f>::func ) ) };

#define REFLECT_STATIC_VERBOSE( _f ) \
int cReflectionHelper<decltype( _f ), _f>::id = cReflectionRegistry::reflectStatic( #_f, __FILE__, __LINE__, (iArgOperator*)&( cReflectionHelper<decltype( _f ), _f>::func ) );

#define REFLECT_STATIC_NAME( _f, _name ) \
int cReflectionHelper<decltype( _f ), _f>::id = cReflectionRegistry::reflectStatic( _name, (iArgOperator*)&( cReflectionHelper<decltype( _f ), _f>::func ) );

#define REFLECT_STATIC_NAME_VERBOSE( _f, _name ) \
int cReflectionHelper<decltype( _f ), _f>::id = cReflectionRegistry::reflectStatic( _name, __FILE__, __LINE__, (iArgOperator*)&( cReflectionHelper<decltype( _f ), _f>::func ) );
