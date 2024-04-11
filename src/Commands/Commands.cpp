#include "Commands.h"

void add( int _a, int _b )
{
	printf( "%i + %i = %i", _a, _b, _a + _b );
}

void help()
{
	for ( auto iter = cReflectionRegistry::m_functions.begin(); iter != cReflectionRegistry::m_functions.end(); ++iter )
	{
		shortFuncSig( iter->second );
		if ( std::next( iter ) != cReflectionRegistry::m_functions.end() )
			printf( "\n" );
	}
}

void help_verbose()
{
	for ( auto iter = cReflectionRegistry::m_functions.begin(); iter != cReflectionRegistry::m_functions.end(); ++iter )
	{
		verboseFuncSig( iter->second );
		if ( std::next( iter ) != cReflectionRegistry::m_functions.end() )
			printf( "\n" );
	}
}


//////////////////////////////////////////////////////
//                   NON STATIC                     //
//////////////////////////////////////////////////////



void verboseFuncSig( sStaticReflection& _desc )
{
	std::vector<std::string> args = _desc.func->getArgsTypeNames();
	printf( "%s(", _desc.name.c_str() );

	// print params
	if ( args.size() > 0 )
	{
		printf( " %s", args[ 0 ].c_str() );
		for ( int i = 1; i < args.size(); i++ )
		{
			printf( ", %s", args[ i ].c_str() );
		}
		printf( " " );
	}

	if( _desc.line != -1 )
		printf( "):\n  %s (%i)", _desc.file.c_str(), _desc.line );
	else
		printf( "):\n  ???" );
}

void shortFuncSig( sStaticReflection& _desc )
{
	std::vector<std::string> args = _desc.func->getArgsTypeNames();
	printf( "%s ", _desc.name.c_str() );

	// print params
	for ( int i = 0; i < args.size(); i++ )
		printf( "[%s] ", args[ i ].c_str() );
}

void funcSig( std::string _func_name )
{
	if ( cReflectionRegistry::m_functions.count( _func_name ) == 0 )
	{
		printf( "Function not found.\n" );
		return;
	}

	sStaticReflection& desc = cReflectionRegistry::m_functions[ _func_name ];
	verboseFuncSig( desc );
}