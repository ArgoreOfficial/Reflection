/*
 * Project generated by Templater
 * Argore 2024
 */


#include "Reflection/Reflection.h"
#include "CommandConsole/cCommandConsole.h"

class cTest
{
public:
	static void runTest();
};
REFLECT_STATIC( cTest::runTest )

static void doThing( int _i );                 REFLECT_STATIC( doThing )
static void doSingleThing();                   REFLECT_STATIC( doSingleThing )
static void funcSig( std::string _func_name ); REFLECT_STATIC( funcSig )

/* impl */
void doThing( int _i ) { printf( "Did thing %i\n", _i ); }
void doSingleThing()   { printf( "no args:(\n" ); }
void cTest::runTest()  { printf( "Ran test\n" ); }

void realFuncSig( sStaticReflection& _desc )
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

	printf( "):\n  %s (%i)\n\n", _desc.file.c_str(), _desc.line );
}

void shortFuncSig( sStaticReflection& _desc )
{
	std::vector<std::string> args = _desc.func->getArgsTypeNames();
	printf( "%s", _desc.name.c_str() );

	// print params
	if ( args.size() > 0 )
	{
		printf( " [%s]", args[ 0 ].c_str() );
		for ( int i = 1; i < args.size(); i++ )
		{
			printf( ", [%s]", args[ i ].c_str() );
		}
		printf( " " );
	}

	printf( "\n" );
}

void funcSig( std::string _func_name )
{
	if ( cReflectionRegistry::m_functions.count( _func_name ) == 0 )
	{
		printf( "Function not found.\n" );
		return;
	}
	
	sStaticReflection& desc = cReflectionRegistry::m_functions[ _func_name ];
	realFuncSig( desc );
}

static void help_verbose()
{
	for ( auto& f : cReflectionRegistry::m_functions )
		realFuncSig( f.second );
} REFLECT_STATIC( help_verbose )
static void help()
{
	for ( auto& f : cReflectionRegistry::m_functions )
		shortFuncSig( f.second );
} REFLECT_STATIC( help )
static void clear() { system( "cls" ); } 

// smaller, but wish I could do auto :(
cReflectionHelper<decltype( clear ), clear>::creator cReflectionHelper<decltype( clear ), clear>::factory{ "clear" };

static bool run = true;
static void program_exit() { run = false; } REFLECT_STATIC_NAME( program_exit, "exit" )

int main()
{
	cCommandConsole command_console;

	while ( run )
	{
		printf( "\n> " );
		sCommand command = command_console.pollNextCommand();

		cReflectionRegistry::callFunction( command.command, command.arguments );
	}

	return 0;
}
