#pragma once

#include <vector>
#include <string>

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
	
};