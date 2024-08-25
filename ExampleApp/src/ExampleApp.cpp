#include "MiniEngine.hpp"
#include "MiniEngineCore.hpp"
#include <cstdlib>
#include <iostream>

int main() {
    MiniEngineCore::HelloWorldTestFunction();
    int a = 100, b = 200;
    std::cout << "Hello from ExampleApp!" << std::endl;
    std::cout << "Build test: " << a << " + " << b << " = " << 
        MiniEngineCore::AddTestFunction(a, b) << std::endl;
    return EXIT_SUCCESS;
}
