#include "core/Tests.hpp"
#include "core/Logging.hpp"
#include "core/MemoryManagement.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <iostream>
#include <stdexcept>

namespace MiniEngineCore {

int AddTestFunction(int a, int b) {
    std::cout << "Testing Add Function" << std::endl;
    return (a + b);
}

void HelloWorldTestFunction() {
    std::cout << "Testing Console OUT, ERR" << std::endl;
    std::cout << "[OUT] Hello world!" << std::endl;
    std::cerr << "[ERR] Hello world!" << std::endl;
}

void RunTests() {
    HelloWorldTestFunction();

    std::cout << "From Console OUT: MiniEngine Running Tests:" << std::endl;
    bool8 init_flag = Logger::Initialize();
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
    int test_val = AddTestFunction(100, 200);
    if (test_val != (a+b)) {
        throw std::logic_error("Test: returned sum did not match expected value = 300");
    }
    else {
        std::cout << "All Tests Cleared!" << std::endl;
    }
}

void BenchmarkSPDLOG(const int32 n_iterations) {
    auto console = spdlog::stdout_color_mt("console");
    for (int32 i = 0; i < n_iterations; i++) {
        spdlog::get("console")->info("Testing SPDLOG: {:4.2f}", 3.141596);
    }
}

void BenchmarkInternalLog(const int32 n_iterations) {
    bool8 init_flag = Logger::Initialize();
    if (init_flag == FALSE) {
        std::cout << "Could not initialize Logger" << std::endl;
        return;
    }

    for (int32 i = 0; i < n_iterations; i++) {
        MLOG_INFO("Testing internal log: %4.2f", 3.141596);
    }
}

void TestMemoryMonitor() {
    MemoryMonitor::Initialize();
    MemoryMonitor::UpdateAllocations(AllocationType::HEAP, AllocationTag::EVENT, 10989);
    MemoryMonitor::UpdateAllocations(AllocationType::STACK, AllocationTag::ARRAY, 178979978);
    MLOG_INFO(MemoryMonitor::GetCurrentUsageStatusByTag());
    MemoryMonitor::Deinitialize();
}

}
