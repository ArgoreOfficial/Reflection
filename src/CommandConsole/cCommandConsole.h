#pragma once

#include <vector>
#include <string>
#include "../Reflection/Reflection.h"

struct sCommand
{
	std::string command;
	std::vector<std::string> arguments;
};

class cCommandConsole
{
public:

	 cCommandConsole() { }
	~cCommandConsole() { }

	sCommand pollNextCommand();
	
	static void doCommand()
	{
		printf( "did command\n" );
	}
};
REFLECT_STATIC_MEMBER( cCommandConsole, doCommand )