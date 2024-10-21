#pragma once

#include "Types.hpp"

namespace MiniEngineCore {

enum class AllocationTag: uint16 {
    UNKNOWN,
    ARRAY,
    DYNAMIC_ARRAY,
    PRIORITY_QUEUE,
    BST,
    DICTIONARY,
    STRING,
    EVENT,
    RENDERER,
    PLATFORM,
    TEXTURE,
    ENTITY,
    NODE,
    APPLICATION,
    GAME,
    SCENE,
    TRANSFORM,
    JOB,
    MEMORY_MANAGEMENT,
    MAX_TAGS
};

enum class AllocationType: uint16 {
    SYSTEM,
    STACK,
    HEAP,
    LINEAR,
    POOL,
    MAX_TYPES
};

// store state of MemoryMonitor
static bool8 MemoryMonitorIsInitialized = FALSE;

// Class that stores global information on memory allocations by Engine / App
class MemoryMonitor {
public:
    // Initialize MemoryMonitor (to be called before instantiating any allocator)
    static bool8 Initialize();
    // Update allocation details:
    static void UpdateAllocations(AllocationType type, AllocationTag tag, uint64 size);
    // Get current memory usage details as string grouped by tag
    static char* GetCurrentUsageStatusByTag();
    // Denitialize MemoryMonitor
    static void Deinitialize();
    // Check if MemoryMonitor is initialized
    static inline bool8 IsInitialized() { return (MemoryMonitorIsInitialized == TRUE); }

    inline static uint64 TotalSizeByTag[(uint64)AllocationTag::MAX_TAGS];
    inline static uint64 TotalSizeByType[(uint64)AllocationType::MAX_TYPES];
    static constexpr const char* TagStrings[(uint64)AllocationTag::MAX_TAGS] = {
        "UNKNOWN            ",
        "ARRAY              ",
        "DYNAMIC_ARRAY      ",
        "PRIORITY_QUEUE     ",
        "BST                ",
        "DICTIONARY         ",
        "STRING             ",
        "EVENT              ",
        "RENDERER           ",
        "PLATFORM           ",
        "TEXTURE            ",
        "ENTITY             ",
        "NODE               ",
        "APPLICATION        ",
        "GAME               ",
        "SCENE              ",
        "TRANSFORM          ",
        "JOB                ",
        "MEMORY_MANAGEMENT  "
    }; 
    static constexpr const char* TypeStrings[(uint64)AllocationType::MAX_TYPES] = {
        "HEAP               ",
        "STACK              ",
        "LINEAR             "
    };
};

}

