#pragma once 

#include "Types.hpp"
#include "MemoryManagement.hpp"

namespace MiniEngineCore {
    MINI_API int AddTestFunction(int a, int b);
    MINI_API void HelloWorldTestFunction(void);
    MINI_API void RunTests(void);
    MINI_API void BenchmarkSPDLOG(const int32 n_iterations);
    MINI_API void BenchmarkInternalLog(const int32 n_iterations);
    MINI_API void TestMemoryMonitor();
    MINI_API void TestWindowSystem();
}

