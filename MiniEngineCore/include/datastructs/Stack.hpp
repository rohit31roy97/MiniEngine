#pragma once

#include "core/Types.hpp"
#include "core/Logging.hpp"
#include "core/Allocators.hpp"

namespace MiniEngineCore {

// Implementation of Stack with fixed capacity
class Stack {
public:
    Stack(uint32 elem_size, uint32 capacity, MemoryAllocator* allocator);
    ~Stack();
    // get last element in stack
    void* pop();
    // push new element into stack
    bool8 push(void* value);

    // standard inline getters:
    uint32 getCapacity() { return mCapacity; }
    uint32 getElementSize() { return mElementSize; }
    void* getStackPointer() { return mStackPointer; }
private:
    MemoryAllocator* mAllocator;
    uint32 mCapacity;
    uint32 mElementSize;
    void* mStackPointer;
    void* mRootPointer;
};

}

