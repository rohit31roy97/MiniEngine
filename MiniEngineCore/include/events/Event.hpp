
#pragma once

#include "core/Types.hpp"
#include <cstring>

namespace MiniEngineCore {

// Event type:
enum class EventType {
    NULL_EVENT,
    APPLICATION_QUIT_EVENT,
    WINDOW_CLOSE_EVENT,
    WINDOW_RESIZE_EVENT,
    KEY_PRESS_EVENT,
    KEY_RELEASE_EVENT,
    BUTTON_PRESS_EVENT,
    BUTTON_RELEASE_EVENT,
    MOUSE_MOVE_EVENT,
    MOUSE_SCROLL_EVENT,
    MAX_EVENTS
};

// Event context data:
typedef struct EventContext {
    union {
        bool8 bool8[16];
        uint32 uint32[4];
        int32 int32[4];
        float32 float32[4];
        uint64 uint64[2];
        int64 int64[2];
        char c[16];
    } data;
} EventContext;


// Base Event class (All other events should derive from this class)
class Event {
public:
    Event();
    ~Event();
    EventContext getContext() { return mContext; }
    EventType getType() { return mEventType; }
    void setContext(EventContext context) { memcpy(&mContext, &context, 128); }
    void setType(EventType type) { mEventType = type; }
private:
    EventContext mContext;
    EventType mEventType;
};


}
