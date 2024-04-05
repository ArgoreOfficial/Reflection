#include "cReflectionRegistry.h"
#include "cReflectedFunction.h"

//std::map<std::string, sReflectionDescriptor> cReflectionRegistry::m_reflection_descriptors = {};

int cReflectionRegistry::registerReflection( const std::string _name, const std::string _file, int _line, iArgOperator* _func )
{
	sReflectionDescriptor desc{
		.id = (int)cReflectionRegistry::m_reflection_descriptors.size(),
		.name = _name,
		.file = _file,
		.line = _line,
		.func = _func
	};

	cReflectionRegistry::m_reflection_descriptors[ desc.name ] = desc;
	return (int)cReflectionRegistry::m_reflection_descriptors.size();
}

void cReflectionRegistry::callFunction( std::string _name, const std::vector<std::string>& _args )
{
	if ( cReflectionRegistry::m_reflection_descriptors.count( _name ) == 0 )
		return;

	iArgOperator* f = cReflectionRegistry::m_reflection_descriptors[ _name ].func;
	( *f )( _args );
}
