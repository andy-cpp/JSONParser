# JSONParser
C++ JSON Parser

About
This is a JSON Parser built purely in c++

Installation

git clone 

Usage

Parse JSON from source

```c++
#include "json.hpp"

int main()
{
  std::string source = R"({"name": "Test", "age": 20})";

  Object object = JSON::Parse(source);
}


```

Notes
