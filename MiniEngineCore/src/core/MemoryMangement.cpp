#include "core/MemoryManagement.hpp"
#include <cstdlib>

/* Implementation for class BaseMemoryAllocator */

MINI_API bool8 MiniEngineCore::BaseMemoryAllocator::initialize() {
    num_allocated = 0;
    for (uint64 i = 0; i <= MAX_NUM_ALLOCATIONS; i++) {
        _allocation_table[i].handle = MINI_INVALID_MEMORY_ADDRESS;
        _allocation_table[i].size = 0;
    }
    // in future might need to do some basic checking like 
    // see if memory is available or some other stuff
    return TRUE;
}

MINI_API void* MiniEngineCore::BaseMemoryAllocator::allocate(uint64 size, bool8 aligned) {
    // TODO: allocate using malloc, and tag allocation header
    return MINI_INVALID_MEMORY_ADDRESS;
}

MINI_API bool8 MiniEngineCore::BaseMemoryAllocator::free(void* handle) {
    return FALSE;
}

MINI_API bool8 MiniEngineCore::BaseMemoryAllocator::memZero(void* handle, uint64 size) {
    return FALSE;
}

MINI_API bool8 MiniEngineCore::BaseMemoryAllocator::memCopy(void* src, void* dest, uint64 size) {
    return FALSE;
}

MINI_API bool8 MiniEngineCore::BaseMemoryAllocator::deinitialize() {
    return FALSE;
}

MINI_API char* MiniEngineCore::BaseMemoryAllocator::getAllocationInfo() {
    return nullptr;
}
