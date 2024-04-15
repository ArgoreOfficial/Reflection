#include "Commands.h"

void add( int _a, int _b )
{
	printf( "%i + %i = %i", _a, _b, _a + _b );
}

void help()
{
	for ( auto iter = cReflectionRegistry::m_functions.begin(); iter != cReflectionRegistry::m_functions.end(); ++iter )
	{
		funcSig( iter->first );
		if ( std::next( iter ) != cReflectionRegistry::m_functions.end() )
			printf( "\n" );
	}
}

//////////////////////////////////////////////////////
//                   NON STATIC                     //
//////////////////////////////////////////////////////

void funcSig( std::string _func_name )
{
	if ( cReflectionRegistry::m_functions.count( _func_name ) == 0 )
	{
		printf( "Function not found.\n" );
		return;
	}

	sStaticReflection& desc = cReflectionRegistry::m_functions[ _func_name ];
	
	std::vector<std::string> args = desc.func->getArgsTypeNames();
	printf( "%s ", desc.name.c_str() );

	// print params
	for ( int i = 0; i < args.size(); i++ )
		printf( "[%s] ", args[ i ].c_str() );
}