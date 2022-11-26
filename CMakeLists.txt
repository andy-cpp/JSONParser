cmake_minimum_required(VERSION 3.10)

file(GLOB SOURCE "*.cpp")

set(CMAKE_CXX_STANDARD 20)


add_executable(JSONParser ${SOURCE})