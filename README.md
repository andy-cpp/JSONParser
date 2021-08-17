# JSONParser
C++ JSON Parser

# About
This is a JSON Parser built purely in c++ with its own lexer and parser

# Installation

Fetch repository: <br>
`git clone https://github.com/uncreativekar/JSONParser.git`<br>
Compile project: <br>
`make`<br>

# Usage

```c++
#include "json.hpp"

int main()
{
  /*
    Parse JSON from source
  */
  std::string source = R"({"name": "Test", "age": 20})";
  
  Object object = JSON::Parse(source);
  
  /*
    Parse JSON from file
  */
  Object object = JSON::LoadFromFile("data.json");
}
```



# Notes

This JSON parser does not support escape characters or unicode yet
