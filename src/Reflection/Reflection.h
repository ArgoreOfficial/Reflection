#pragma once

#include "cReflectedFunction.h"
#include "cReflectionRegistry.h"

// MACRO


#define REFLECT_STATIC( _f ) \
Reflect<_f> Reflector<_f>::creator{ #_f };

#define REFLECT_STATIC_VERBOSE( _f ) \
Reflect<_f> Reflector<_f>::creator{ #_f };

#define REFLECT_STATIC_NAME( _f, _name ) \
Reflect<_f> Reflector<_f>::creator{ _name };

#define REFLECT_STATIC_NAME_VERBOSE( _f, _name ) \
Reflect<_f> Reflector<_f>::creator{ _name };
