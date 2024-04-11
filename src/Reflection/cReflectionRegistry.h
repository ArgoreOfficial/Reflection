#pragma once

#include <string>
#include <map>
#include <vector>

class iArgOperator;

struct sStaticReflection
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
	static inline std::map<std::string, sStaticReflection> m_functions;

	static int  reflectStatic( const std::string _name, const std::string _file, int _line, iArgOperator* _func );
	static int  reflectStatic( const std::string _name, iArgOperator* _func );
	static void callFunction ( std::string _name, const std::vector<std::string>& _args = {} );
};