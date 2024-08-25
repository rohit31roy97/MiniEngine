cmake_minimum_required(VERSION 3.30.2)

project(ExampleApp VERSION 0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ExampleApp src/ExampleApp.cpp)

target_link_libraries(${PROJECT_NAME}
    miniengine::minienginecorelib
)

