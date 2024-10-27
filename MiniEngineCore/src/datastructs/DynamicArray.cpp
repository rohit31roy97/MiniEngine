#include "datastructs/DynamicArray.hpp"
#include "core/MemoryManagement.hpp"
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
    // check if index within bound
    if (index > mLength) {
        MLOG_ERROR("DynamicArray query index out of bounds");
        return 0;
    }
    // return element at query index
    uint8* ptr = (uint8*) mElements;
    return (ptr + index * mElementSize);
}

bool8 DynamicArray::setAt(uint32 index, void* value) {
    // check if index within bounds
    if (index > mLength) {
        MLOG_ERROR("DynamicArray query index out of bounds");
        return FALSE;
    }
    // insert value at query index
    uint8* ptr = (uint8*) mElements;
    memcpy(ptr + index * mElementSize, value, mElementSize);
    return TRUE;
}

bool8 DynamicArray::insertAt(uint32 index, void* value) {
    // check if index within bounds
    if (index >= mLength) {
        MLOG_ERROR("DynamicArray query index out of bounds");
        return FALSE;
    }
    // if array already at capacity, expand it
    if (mLength == mCapacity) {
        this->expandArray(2*mCapacity);
    }
    // move elements over to temporary buffer to create space for insertion
    uint8* ptr = (uint8*) mElements;
    uint32 temp_size = (mLength-index)*mElementSize;
    uint8* tmp = (uint8*) mAllocator->allocate(temp_size, AllocationTag::ARRAY, FALSE);
    if (tmp == 0) {
        MLOG_ERROR("Allocator failed to allocate memory for temporary buffer");
        return FALSE;
    }
    // insert element and swap between self and temp buffer
    memcpy(tmp, ptr+index, temp_size);
    memcpy(ptr+index, value, mElementSize);
    memcpy(ptr+index+1, tmp, temp_size);
    mAllocator->deallocate(tmp, AllocationTag::ARRAY, temp_size);
    mLength += 1;
    return TRUE;
}

bool8 DynamicArray::removeFrom(uint32 index) {
    // check if index within bounds
    if (index >= mLength) {
        MLOG_ERROR("DynamicArray query index out of bounds");
        return FALSE;
    }
    // move elements over one byte at a time
    uint8* ptr = (uint8*)mElements;
    memcpy(ptr+index, ptr+index+1, (mLength-index-1));
    memset(ptr+mLength, 0, mElementSize);
    mLength -= 1;
    return TRUE;
}

bool8 DynamicArray::copyFromList(void* list, uint32 num_elements) {
    if (num_elements > mCapacity) {
        if (!this->expandArray(mCapacity * 2)) {
            MLOG_ERROR("Allocator failed to allocate memory for DynamicArray");
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

