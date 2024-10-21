#include "core/Types.hpp"
#include "core/Logging.hpp"
#include "core/MemoryManagement.hpp"
#include "core/Allocators.hpp"
#include "core/Assertions.hpp"
#include <cstdlib>
#include <cstring>

namespace MiniEngineCore {

// SystemAllocator definitions:
void* SystemAllocator::allocate(uint64 size, AllocationTag tag, bool8 aligned) {
    if (!MemoryMonitor::IsInitialized()) {
        MLOG_ERROR("MemoryMonitor must be initialized before any memory allocations");
        return 0;
    }

    // TODO: handle alignments here?
    void* handle = (void*) malloc(size);
    // If malloc ever fails, we're probably screwed and should stop everything and break:
    MASSERT_STRICT_MSG(handle != 0, "malloc failed to allocate memory.");
    memset(handle, 0, size);
    MemoryMonitor::UpdateAllocations(AllocationType::SYSTEM, tag, size);
    return handle;
}

void SystemAllocator::deallocate(void* handle, AllocationTag tag, uint64 size) {
    // TODO: maybe surround with try / catch blocks?
    free(handle);
    MemoryMonitor::UpdateAllocations(AllocationType::SYSTEM, tag, -size);
}
// - - - - - - - - - - - - - -

// StackAllocator definitions:
// - - - - - - - - - - - - - -

// LinearAllocator definitions:
// - - - - - - - - - - - - - -

// PoolAllocator definitions:
// - - - - - - - - - - - - - -
} 
