#include "cCommandConsole.h"

#include <iostream>
#include <sstream>

sCommand cCommandConsole::pollNextCommand()
{
	sCommand command{};

	std::string input;
	std::getline( std::cin, input );

	std::istringstream iss( input );
	std::string intermediate_string;

	std::getline( iss, command.command, ' ' );
	
	while ( std::getline( iss, intermediate_string, ' ' ) )
		command.arguments.push_back( intermediate_string );
	
    return command;
}
