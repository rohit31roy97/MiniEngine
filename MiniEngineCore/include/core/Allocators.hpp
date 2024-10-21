#pragma once
#include "Types.hpp"
#include "MemoryManagement.hpp"

namespace MiniEngineCore {

// Base virtual MemoryAllocator class:
class MemoryAllocator {
public:
    virtual void* allocate(uint64 size, AllocationTag tag, bool8 aligned) = 0;
    virtual void deallocate(void* handle, AllocationTag tag, uint64 size) = 0;
};

// System allocator (wrapper for malloc/free)
class SystemAllocator : MemoryAllocator {
public:
    void* allocate(uint64 size, AllocationTag tag, bool8 aligned) override;
    void deallocate(void* handle, AllocationTag tag, uint64 size) override;
};

/* Custom Allocators to handle special use cases:
 *  - StackAllocator:
 *  - LinearAllocator:
 *  - PoolAllocator:
 *  - HeapAllocator:
 */

class StackAllocator : MemoryAllocator {
};

class LinearAllocator : MemoryAllocator {
};

class PoolAllocator : MemoryAllocator {
};

class HeapAllocator : MemoryAllocator {
};

}
