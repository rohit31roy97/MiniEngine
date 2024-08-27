#include "Tests.hpp"
#include "Logging.hpp"

#include <iostream>
#include <stdexcept>


MINI_API int MiniEngineCore::AddTestFunction(int a, int b) {
    std::cout << "Testing Add Function" << std::endl;
    return (a + b);
}

MINI_API void MiniEngineCore::HelloWorldTestFunction() {
    std::cout << "Testing Console OUT, ERR" << std::endl;
    std::cout << "[OUT] Hello world!" << std::endl;
    std::cerr << "[ERR] Hello world!" << std::endl;
}

MINI_API void MiniEngineCore::RunTests() {
    MiniEngineCore::HelloWorldTestFunction();

    std::cout << "From Console OUT: MiniEngine Running Tests:" << std::endl;
    bool8 init_flag = MiniEngineCore::Logger::Initialize();
    if (init_flag == FALSE) {
        std::cout << "Could not initialize Logger" << std::endl;
        return;
    }

    std::cout << "Logger initialized" << std::endl;
    std::cout << "Testing all log levels" << std::endl;

    MLOG_FATAL("Testing FATAL %3.3f", 3.14);
    MLOG_ERROR("Testing ERROR %3.3f", 3.14);
    MLOG_WARN("Testing WARN %3.3f", 3.14);
    MLOG_DEBUG("Testing DEBUG %3.3f", 3.14);
    MLOG_INFO("Testing INFO %3.3f", 3.14);
    MLOG_TRACE("Testing TRACE %3.3f", 3.14);

    const int a = 200;
    const int b = 100;
    int test_val = MiniEngineCore::AddTestFunction(100, 200);
    if (test_val != (a+b)) {
        throw std::logic_error("Test: returned sum did not match expected value = 300");
    }
    else {
        std::cout << "All Tests Cleared!" << std::endl;
    }
}

