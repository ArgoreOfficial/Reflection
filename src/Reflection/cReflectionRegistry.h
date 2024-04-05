#pragma once

#include <string>
#include <map>


#include <vector>

class iArgOperator;

struct sReflectionDescriptor
{
	int id;
	std::string name;
	std::string file;
	int line;
	iArgOperator* func;
};

class cReflectionRegistry
{
public:
	static inline std::map<std::string, sReflectionDescriptor> m_reflection_descriptors;

	static int  registerReflection( const std::string _name, const std::string _file, int _line, iArgOperator* _func );
	static void callFunction      ( std::string _name, const std::vector<std::string>& _args = {} );
};