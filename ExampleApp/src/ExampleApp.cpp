#include "MiniEngine.hpp"
#include <cstdlib>
/*#include <time.h>*/

int main() {
    MiniEngineCore::RunTests();
    MASSERT(1 > 0);
    MASSERT(1 == 0);
    MiniEngineCore::TestMemoryMonitor();

    /*time_t rawtime;*/
    /*struct tm* timeinfo;*/
    /*time( &rawtime );*/
    /*timeinfo = localtime(&rawtime);*/
    /*printf("TIME: %s", asctime(timeinfo));*/
    /**/
    /*//MiniEngineCore::BenchmarkInternalLog(1000000);*/
    /*MiniEngineCore::BenchmarkSPDLOG(1000000);*/
    /**/
    /*time( &rawtime );*/
    /*timeinfo = localtime(&rawtime);*/
    /*printf("TIME: %s", asctime(timeinfo));*/

    return EXIT_SUCCESS;
}
