#include <iostream>
#include <assert.h>


#include "json.hpp"


int main()
{
    auto obj = JSON::LoadFromFile("data.json");
    
    obj.Set("data", 100);
    
    std::cout << JSON::ToString(obj) << "\n";
}