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
    MAX_TAGS
};

enum class AllocationType: uint16 {
    STACK,
    HEAP,
    LINEAR,
    MAX_TYPES
};


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
        "JOB                "
    }; 
    static constexpr const char* TypeStrings[(uint64)AllocationType::MAX_TYPES] = {
        "HEAP               ",
        "STACK              ",
        "LINEAR             "
    };
};

// Simple Heap Allocator class:
class HeapAllocator {
public:
    // Initialize HeapAllocator instance:
    HeapAllocator(uint64 initial_size);
    // Allocate memory and return pointer to starting address:
    void* allocate(uint64 size, AllocationTag tag, bool8 aligned);
    // Deallocate memory pointed to by handle:
    void deallocate(void* handle);
    // Deinitialize HeapAllocator instance:
    ~HeapAllocator();
private:
    // Struct to represent a memory block (stream of bytes)
    typedef struct MemoryBlock {
        uint64 size; // size of block
        uint8* address; // starting address of block
    } MemoryBlock;
    static const uint16 MaxAssignedBlocks = 1024; // Max can assign 1024 blocks of memory
    static const uint16 TotalBlocks = 64; // Heap can ask for total 64 blocks of memory to assign from
    static const uint64 MaxBlockSize = 1024*1024*64; // Each block allocated using malloc is of max size 64
    MemoryBlock mAssignedBlocks[MaxAssignedBlocks]; // Array to store all blocks assigned by heap
    MemoryBlock mAvailableBlocks[MaxAssignedBlocks]; // Array to store all available blocks in heap
    uint8* mBlocksToFree[TotalBlocks]; // Array to store addresses of all blocks added to heap (to free)
    uint16 mNumAssignedBlocks; // Number of blocks assigned by heap
    uint16 mNumAvailableBlocks; // Number of blocks available to assign by heap
    uint64 mTotalHeapSize; // Total size of memory owned by heap
    bool8 addBlockToHeap(); // Allocate a new block and add to list of blocks available in Heap
    uint8* allocateFromBlock(MemoryBlock* block, uint64 size); // Allocate size of memory from specific block
};

// Simple Stack Allocator class:
class StackAllocator {
public:
    // Initialize StackAllocator instance:
    StackAllocator(uint64 size);
    // Allocate new block from stack:
    void* allocate(uint64 size, AllocationTag tag, bool8 aligned);
    // Deallocate last allocation from stack:
    void deallocate();
    // Deinitialize StackAllocator instance:
    ~StackAllocator();
private:
    uint64 mTotalStackSize; // Total size of the memory owned by stack
    uint64 mAvailableStackSize; // Available size of the stack
    uint64 mLastAssignedSize; // Size of last allocation (before current address)
    uint8* mStartAddress; // Starting address of memory owned by stack
    uint8* mCurrentAddress; // Current address of the stack available for allocation
    uint8* pop(uint64 size); // Pop last assigned memory from stack
    uint8* push(uint64 size); // Push new assignment of memory from stack
};

// Simple Linear Allocator class:
class LinearAllocator {
public:
    // Initialize LinearAllocator instance:
    LinearAllocator(uint64 heap_size);
    // Allocate new linear block
    void* allocate(uint64 size, AllocationTag tag, bool8 aligned);
    // Deallocate all allocated linear blocks
    void deallocate();
    // Deinitialize LinearAllocator instance:
    ~LinearAllocator();
private:
    uint64 mTotalSize; // Total size of memory owned by allocator
    uint64 mAvailableSize; // Size of memory available to allocate by allocator
    uint8* mStartAddress; // Starting address of memory owned by allocator
    uint8* mCurrentAddress; // Current address of memory available to allocate
    uint8* _allocate(uint64 size);
};

}

