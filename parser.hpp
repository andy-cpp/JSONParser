#pragma once
#include "Object.hpp"


struct ParserContext {
	char const* src = 0; // source json string
	size_t length = 0;
	size_t index = 0; // current position of parser relative to src
	
};

class Parser
{
public:
	Parser(char const* src);

	Object Parse();

private:
	ParserContext context;
};