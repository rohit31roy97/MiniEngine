#include "MiniEngineCore.hpp"
#include <iostream>

int MiniEngineCore::AddTestFunction(int a, int b) {
    return a + b;
}

void MiniEngineCore::HelloWorldTestFunction() {
    std::cout << "Console OUT: Hello World!" << std::endl;
    std::cerr << "Console ERR: Hello World!" << std::endl;
}
