#pragma once

#include "core/Types.hpp"
#include "core/Logging.hpp"
#include "core/MemoryManagement.hpp"

namespace MiniEngineCore {

class DynamicArray {
public:
    DynamicArray(uint32 elem_size, uint32 capacity, MemoryAllocator* allocator);
    ~DynamicArray();
    // get pointer to value at index 
    void* getAt(uint32 index);
    // set value at index to new value
    bool8 setAt(uint32 index, void* value);
    // insert new value at index
    bool8 insertAt(uint32 index, void* value);
    // delete element at index
    bool8 removeFrom(uint32 index);
    // copy from another DynamicArray / List of elements
    bool8 copyFromList(void* list, uint32 num_elements);

    // standard inline getters:
    uint32 getLength() { return mLength; }
    uint32 getCapacity() { return mCapacity; }
    uint32 getElementSize() { return mElementSize; }
    void* getElements() { return mElements; }
private:
    MemoryAllocator* mAllocator;
    uint32 mCapacity;
    uint32 mLength;
    uint32 mElementSize;
    void* mElements;
    // expand the array (using a new allocation) to have higher new capacity
    bool8 expandArray(uint32 new_capacity);
};

}

