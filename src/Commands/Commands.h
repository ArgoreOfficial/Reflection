#pragma once

#include "../Reflection/Reflection.h"

/*
 * reflected functions have to be static, for now ;)
 */

static void funcSig     ( std::string _func_name ); REFLECT_STATIC( funcSig )
static void add         ( int _a, int _b );         REFLECT_STATIC( add )
static void help        ( void );                   REFLECT_STATIC( help )


/*
 * 
 * Playing around with other ways of reflecting
 * Pushed it down to a very basic 'Reflector<function>' static initialization
 * Still want to improve it 
 * 
*/
	

template<auto f, class F = decltype( *f )>
struct Reflect2
{
	Reflect2( const std::string _name )
	{
		static cReflectedFunction func( f );
		cReflectionRegistry::reflectStatic( _name, (iArgOperator*)( &func ) );
	}
};

template<auto f, class F = decltype( *f )>
class Reflector2
{
public:
	static const char* name;
	static const inline Reflect2<f, F> creator{ name };
};


static void clear()
{
	system( "cls" );
}

// Reflect<clear> Reflector<clear>::creator{ "clear" };
const char* Reflector2<clear>::name = "clearNOW";