#pragma once

#include "events/Event.hpp"
#include "core/MemoryManagement.hpp"

namespace MiniEngineCore {

// Event callback function signature
typedef bool8 (*EventCallback) (EventType type, EventContext context, void* sender);



MINI_API class EventManager {
public:
    static bool8 Initialize();
    static void Deinitialize();
    static bool8 RegisterCallback(EventType type, void* listener, EventCallback handler);
    static bool8 UnregisterCallback(EventType type, void* listener, EventCallback handler);
    static void ExtendRegisterList(EventType type, uint64 size);
private:
    static inline uint32 NumRegisteredCallbacks[(uint32)EventType::MAX_EVENTS];
    // TODO: change to use a DynamicArray of EventCallbacks:
    static inline EventCallback* RegisteredCallbacks[(uint32)EventType::MAX_EVENTS];
    static inline bool8 Initialized = TRUE;
};


}

