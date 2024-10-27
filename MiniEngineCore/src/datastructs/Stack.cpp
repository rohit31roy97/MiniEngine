#include "datastructs/Stack.hpp"
#include <cstring>

namespace MiniEngineCore {

Stack::Stack(uint32 elem_size, uint32 capacity, MemoryAllocator* allocator){
    mAllocator = 0;
    mCapacity = 0;
    mElementSize = 0;
    mStackPointer = 0;
    mRootPointer = 0;
    uint8* handler = (uint8*) allocator->allocate(capacity*elem_size, AllocationTag::STACK, FALSE);
    if (handler == 0) {
        MLOG_ERROR("Allocator could not allocate memory to stack");
        return;
    }
    mAllocator = allocator;
    mElementSize = elem_size;
    mCapacity = capacity;
    mRootPointer = handler;
    mStackPointer = handler;
}

Stack::~Stack() {
    if (mRootPointer == 0) {
        MLOG_WARN("Stack root pointer is NULL, doing nothing!");
        return;
    }
    mAllocator->deallocate(mRootPointer, AllocationTag::STACK, mCapacity * mElementSize);
    mCapacity = 0;
    mStackPointer = 0;
    mRootPointer = 0;
    mElementSize = 0;
}

void* Stack::pop() {
    if (mStackPointer == 0 || mStackPointer == mRootPointer) {
        MLOG_ERROR("Stack empty, cannot pop");
        return 0;
    }
    uint8* ptr = (uint8*) mStackPointer;
    mStackPointer = ptr - mElementSize;
    return ptr;
}

bool8 Stack::push(void* value) {
    if (mStackPointer == 0) {
        MLOG_ERROR("Stack uinitialized, cannot push");
        return FALSE;
    }
    uint8* ptr = (uint8*)mStackPointer;
    uint8* root = (uint8*)mRootPointer;
    if (ptr - root == mCapacity + 1) {
        MLOG_ERROR("Stack full, cannot push");
        return FALSE;
    }
    memcpy(mStackPointer, value, mElementSize);
    mStackPointer = ptr + mElementSize;
    return TRUE;
}

}
