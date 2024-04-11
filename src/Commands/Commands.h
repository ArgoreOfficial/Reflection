#pragma once

#include "../Reflection/Reflection.h"

/*
 * reflected functions have to be static, for now ;)
 */

static void funcSig     ( std::string _func_name ); REFLECT_STATIC_VERBOSE( funcSig )
static void add         ( int _a, int _b );         REFLECT_STATIC( add )
static void help        ( void );                   REFLECT_STATIC( help )
static void help_verbose( void );                   REFLECT_STATIC( help_verbose )

void verboseFuncSig ( sStaticReflection& _desc );
void shortFuncSig( sStaticReflection& _desc );

/* 
 * experimenting with other ways of reflecting 
 *
 * this uses the constructor as a "function"
 * it's slightly smaller, and all the casting is done in the constructor
 * rather than right here, although it's still pretty cluttered
 * 
 */

static void clear() { system( "cls" ); }
cReflectionHelper<decltype( clear ), clear>::creator cReflectionHelper<decltype( clear ), clear>::factory{ "clear" };
