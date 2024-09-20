#include "core/Logging.hpp"
#include "events/EventManager.hpp"
#include "events/Event.hpp"
#include <cstdlib>
#include <cstring>

namespace MiniEngineCore {

bool8 EventManager::Initialize() {
    // EventManager already initialized (globally), throw warning and quit
    if (Initialized) {
        MLOG_WARN("EventManager::Initialize() called while already initialized.");
        return FALSE;
    }
    // Initialize EventManager
    for (uint32 code=0; code<(uint32)EventType::MAX_EVENTS; code++) {
        // TODO: Switch from malloc to using a specific allocator type. The allocator 
        // should be of a fixed type and probably stored as a static variable for future
        // usage during heap expansion to accommodate additional registrations.
        RegisteredCallbacks[code] = (EventCallback*)malloc(64 * sizeof(EventCallback));
        NumRegisteredCallbacks[code] = 0;
        MaxNumRegisteredCallbacks[code] = 64;
    }
    MLOG_INFO("EventManager initialized successfully.");
    return TRUE;
}

void EventManager::Deinitialize() {
    // Not initialized, throw warning and return
    if (!Initialized) {
        MLOG_WARN("EventManager::Deinitialize() called without initializing first.");
        return;
    }
    // Deinitialize EventManager
    for (uint32 code=0; code<(uint32)EventType::MAX_EVENTS; code++) {
        // TODO: Switch from using C-stdlib malloc/free to custom allocator/deallocator 
        // See comments above in EventManager::Initialize()
        free(RegisteredCallbacks[code]);
        NumRegisteredCallbacks[code] = 0;
        MaxNumRegisteredCallbacks[code] = 0;
    }
    MLOG_INFO("EventManager deinitialized successfully.");
}

bool8 EventManager::RegisterCallback(EventType type, void *listener, EventCallback handler) {
    if (!Initialized) {
        MLOG_ERROR("Cannot register events as EventManager not initialized");
        return FALSE;
    }
    uint32 code = (uint32)type;
    // If not enough memory in register, expand first:
    if (NumRegisteredCallbacks[code] >= MaxNumRegisteredCallbacks[code]) {
        ExtendRegisterList(type, MaxNumRegisteredCallbacks[code]*2);
    }
    // Register event:
    RegisteredCallbacks[code][NumRegisteredCallbacks[code]] = handler;
    NumRegisteredCallbacks[code] += 1;
    MLOG_DEBUG("Registered Event Listener [EventCode: %d]", code);
    return TRUE;
}

bool8 EventManager::UnregisterCallback(EventType type, void *listener, EventCallback handler) {
    if (!Initialized) {
        MLOG_ERROR("Cannot unregister events as EventManager not initialized");
        return FALSE;
    }
    uint32 code = (uint32)type;
    if (NumRegisteredCallbacks[code] == 0) {
        MLOG_WARN("No events registered to [EventCode: %d]", code);
        return FALSE;
    }
    bool8 found = FALSE;
    for (uint32 i=0; i<NumRegisteredCallbacks[code]; i++) {
        if (memcmp(&handler, &RegisteredCallbacks[code][i], sizeof(EventCallback))) {
            // ISSUE: Needs to be implemented using dynamic arrays to pop off element from list
            // consider list structure with constant time access potentially?
            // For now just fails and returns FALSE
            MLOG_FATAL("Feature unimplemented!");
            return FALSE;
        }
    }
    return FALSE;
}

bool8 EventManager::ExtendRegisterList(EventType type, uint64 size) {
    uint32 code = (uint32)type;
    // Check if provided new size is reasonable:
    if (MaxNumRegisteredCallbacks[code] > size) {
        MLOG_ERROR("Provided new size (%d) is smaller that current size (%d)", size, MaxNumRegisteredCallbacks[code]);
        return FALSE;
    }
    // Expand allocation
    // TODO: Switch from using C-stdlib malloc/free to custom allocator/deallocator
    EventCallback* new_list = (EventCallback*)malloc(size * sizeof(EventCallback));
    if (!new_list) {
        MLOG_ERROR("Malloc failed for EventCallback list expansion [EventCode: %d]", type);
        return FALSE;
    }
    else {
        // TODO: Switch from using C-stdlib malloc/free to custom allocator/deallocator
        memcpy(new_list, RegisteredCallbacks[code], NumRegisteredCallbacks[code] * sizeof(EventCallback));
        free(RegisteredCallbacks[code]);
        RegisteredCallbacks[code] = new_list;
        MaxNumRegisteredCallbacks[code] = size;
        MLOG_DEBUG("EventCallback list for [EventCode: %d] expanded to %d from %d", type, size, NumRegisteredCallbacks[code]);
        return TRUE;
    }
}

/*public:*/
/*    static bool8 Initialize();*/
/*    static void Deinitialize();*/
/*    static bool8 RegisterCallback(EventType type, void* listener, EventCallback handler);*/
/*    static bool8 UnregisterCallback(EventType type, void* listener, EventCallback handler);*/
/*    static void ExtendRegisterList(EventType type, uint64 size);*/
/*private:*/
/*    // Event register struct:*/
/*    // TODO: change to use a DynamicArray of EventCallbacks:*/
/*    static inline EventCallback* RegisteredCallbacks[(uint32)EventType::MAX_EVENTS];*/
/*    static inline bool8 Initialized = TRUE;*/
/*}*/
/**/
}
