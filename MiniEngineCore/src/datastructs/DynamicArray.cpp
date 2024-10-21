#include "datastructs/DynamicArray.hpp"
#include <cstdlib>
#include <cstring>

#define MAX(a, b) ((a) < (b)) ? (b) : (a)

namespace MiniEngineCore {

DynamicArray::DynamicArray(uint32 elem_size, uint32 capacity, MemoryAllocator* allocator) {
    mCapacity = 0;
    mLength = 0;
    mElementSize = 0;
    mElements = 0;
    mAllocator = allocator;
    void* handler = (allocator->allocate(elem_size * capacity, AllocationTag::ARRAY, FALSE));

    if (handler) {
        mCapacity = capacity;
        mElementSize = elem_size;
        mElements = handler;
    }
    else {
        MLOG_ERROR("DynamicArray memory allocation failed");
    }
}

DynamicArray::~DynamicArray() {
    mAllocator->deallocate(mElements, AllocationTag::ARRAY, mCapacity * mElementSize);
}

void* DynamicArray::getAt(uint32 index) {
    if (index >= mLength) {
        MLOG_ERROR("DynamicArray query index out of bounds");
        return 0;
    }

    uint8* ptr = (uint8*) mElements;
    return (ptr + index);
}

bool8 DynamicArray::setAt(uint32 index, void* value) {
    if (index >= mLength) {
        MLOG_ERROR("DynamicArray query index out of bounds");
        return FALSE;
    }
    uint8* ptr = (uint8*) mElements;
    ptr = ptr + index;
    memcpy(ptr, value, mElementSize);
    return TRUE;
}

bool8 DynamicArray::insertAt(uint32 index, void* value) {
    // TODO: 
}

bool8 DynamicArray::removeFrom(uint32 index) {
    // TODO:
}

bool8 DynamicArray::copyFromList(void* list, uint32 num_elements) {
    if (num_elements > mCapacity) {
        if (!this->expandArray(mCapacity * 2)) {
            return FALSE;
        }
    }
    memcpy(mElements, list, num_elements*mElementSize);
    mLength = MAX(num_elements, mLength);
    return TRUE;
}

bool8 DynamicArray::expandArray(uint32 new_capacity) {
    if (new_capacity < mCapacity) {
        MLOG_WARN("Ignoring request to shrink DynamicArray");
        return FALSE;
    }
    void* new_handler = (mAllocator->allocate(mElementSize * new_capacity, AllocationTag::ARRAY, FALSE));
    if (!new_handler) {
        MLOG_ERROR("DynamicArray memory allocation failed");
        return FALSE;
    }
    memcpy(new_handler, mElements, mLength*mElementSize);
    mAllocator->deallocate(mElements, AllocationTag::ARRAY, mLength*mElementSize);
    mElements = new_handler;
    mCapacity = new_capacity;
    return TRUE;
}

}

