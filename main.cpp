#include <iostream>
#include <assert.h>
#include <string>

#include "json.hpp"
#include "parser.hpp"

int main()
{
	try {
		std::cout << JSON::LoadFromFile("data.json").Dump() << "\n";
		
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}
}