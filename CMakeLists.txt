cmake_minimum_required(VERSION 3.30.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MiniEngine VERSION 0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(MiniEngineCore)
add_subdirectory(ExampleApp)
