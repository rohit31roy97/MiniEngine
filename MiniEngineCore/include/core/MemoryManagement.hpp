#include "Types.hpp"
#define MINI_INVALID_MEMORY_ADDRESS 0
#define MAX_NUM_ALLOCATIONS 256

namespace MiniEngineCore {


// Basic Interface to be inherited by all Allocators:
MINI_API class MemoryAllocatorInterface {
public:
    // Initialize allocator internally
    virtual bool8 initialize() = 0;
    // Allocate memory (size) with or without alignment (aligned),
    // return a valid address if successful, nullptr otherwise
    virtual void* allocate(uint64 size, bool8 aligned) = 0;
    // Free memory pointed to by handle, returns TRUE is successful
    // FALSE otherwise
    virtual bool8 free(void* handle) = 0;
    // Zero out memory
    virtual bool8 memZero(void* handle, uint64 size) = 0;
    // Copy memory
    virtual bool8  memCopy(void* src, void* dest, uint64 size) = 0;
    // Deinitialize Allocator
    virtual bool8 deinitialize() = 0;
    virtual ~MemoryAllocatorInterface() = default;

protected:
    // Struct to store actual allocation
    typedef struct Allocation {
        uint64 size;
        void* handle;
    } Allocation;

};

// Basic Memory Allocator based on malloc in stdlib:
MINI_API class BaseMemoryAllocator : public MemoryAllocatorInterface {
public:
    bool8 initialize() override;
    void* allocate(uint64 size, bool8 aligned) override;
    bool8 free(void* handle) override;
    bool8 memZero(void* handle, uint64 size) override;
    bool8 memCopy(void* src, void* dest, uint64 size) override;
    bool8 deinitialize() override;
    char* getAllocationInfo();
private:
    // list of blocks allocated by this allocator:
    Allocation _allocation_table[MAX_NUM_ALLOCATIONS];
    // check if allocator has been initialized
    bool8 _is_initialized;
    // number of blocks allocated:
    uint64 num_allocated;
};

}
