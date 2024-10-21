#include "core/MemoryManagement.hpp"
#include "core/Logging.hpp"
#include <cstdlib>
#include <cstdio>
#include <cstring>

namespace MiniEngineCore {

/* Class MemoryMonitor Definitions */
bool8 MemoryMonitor::Initialize() {
    if (MemoryMonitorIsInitialized) {
        MLOG_WARN("MemoryMonitor already initialized");
        return TRUE;
    }

    for (uint64 i = 0; i < (uint64)AllocationTag::MAX_TAGS; i++) {
        TotalSizeByTag[i] = 0;
    }
    for (uint64 i = 0; i < (uint64)AllocationType::MAX_TYPES; i++) {
        TotalSizeByType[i] = 0;
    }
    // Future TODO: Run checks for memory related stuff and then return TRUE/FALSE
    MemoryMonitorIsInitialized = TRUE;
    return TRUE;
}

void MemoryMonitor::UpdateAllocations(AllocationType type, AllocationTag tag, uint64 size) {
    TotalSizeByTag[(uint64)tag] += size;
    TotalSizeByType[(uint64)type] += size;
}

char* MemoryMonitor::GetCurrentUsageStatusByTag() {
    const uint64 KB = 1024;
    const uint64 MB = 1024 * KB;
    const uint64 GB = 1024 * MB;
    char usage_str[4000] = "Memory usage (by tag):\n";
    uint64 offset = strlen(usage_str);
    for (uint32 i = 0; i < (uint32)AllocationTag::MAX_TAGS; i++) {
        char unit[4] = "XiB";
        float size = 1.0;
        if (TotalSizeByTag[i] <= KB) {
            unit[0] = 'B'; unit[1] = 0;
            size = (float)TotalSizeByTag[i];
        }
        else if (TotalSizeByTag[i] <= MB) {
            unit[0] = 'K';
            size = TotalSizeByTag[i]/(float)KB;
        }
        else if (TotalSizeByTag[i] <= GB) {
            unit[0] = 'M';
            size = TotalSizeByTag[i]/(float)MB;
        }
        else {
            unit[0] = 'G';
            size = TotalSizeByTag[i]/(float)GB;
        }
        uint32 written = snprintf(usage_str + offset, 1000, " %s: %8.2f%s\n", TagStrings[i], size, unit);
        offset += written;
    }
    char* final_str = strdup(usage_str);
    return final_str;
}

void MemoryMonitor::Deinitialize() {
    if (!MemoryMonitorIsInitialized) {
        MLOG_WARN("Cannot deinitialize, MemoryMonitor not initialized.");
        return;
    }

    for (uint64 i = 0; i < (uint64)AllocationTag::MAX_TAGS; i++) {
        if (TotalSizeByTag[i] >= 1024) {
            MLOG_ERROR("Memory leak detected in TAG: %s", TagStrings[i]);
        }
    }
    for (uint64 i = 0; i < (uint64)AllocationType::MAX_TYPES; i++) {
        if (TotalSizeByTag[i] >= 1024) {
            MLOG_ERROR("Memory leak detected in TYPE: %s", TypeStrings[i]);
        }
    }
    MemoryMonitorIsInitialized = FALSE;
    return;
}

}
