#include "cReflectionRegistry.h"
#include "cReflectedFunction.h"

//std::map<std::string, sStaticReflection> cReflectionRegistry::m_functions = {};

int cReflectionRegistry::reflectStatic( const std::string _name, const std::string _file, int _line, iArgOperator* _func )
{
	sStaticReflection desc{
		.id = (int)cReflectionRegistry::m_functions.size(),
		.name = _name,
		.file = _file,
		.line = _line,
		.func = _func
	};

	cReflectionRegistry::m_functions[ desc.name ] = desc;
	return (int)cReflectionRegistry::m_functions.size();
}

int cReflectionRegistry::reflectStatic( const std::string _name, iArgOperator* _func )
{
	sStaticReflection desc{
		.id = (int)cReflectionRegistry::m_functions.size(),
		.name = _name,
		.file = "unknown file",
		.line = 0,
		.func = _func
	};

	cReflectionRegistry::m_functions[ desc.name ] = desc;
	return (int)cReflectionRegistry::m_functions.size();
}

void cReflectionRegistry::callFunction( std::string _name, const std::vector<std::string>& _args )
{
	if ( cReflectionRegistry::m_functions.count( _name ) == 0 )
		return;

	iArgOperator* f = cReflectionRegistry::m_functions[ _name ].func;
	( *f )( _args );
}
