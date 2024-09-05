#include "events/Event.hpp"
#include "core/Logging.hpp"
#include <cstring>

namespace MiniEngineCore {

/***** Definitions for class Event *****/
Event::Event() {
    mEventType = EventType::NULL_EVENT;
    memset(&mContext, 0, 128);
    MLOG_DEBUG("New event generated");
}

Event::~Event() {
    MLOG_DEBUG("Event deleted");
    // TODO: once even is deleted, unregister all callbacks to it from EventManager
}




/*// Base Event class (All other events should derive from this class)*/
/*class Event {*/
/*public:*/
/*    Event();*/
/*    ~Event();*/
/*    EventContext getContext() { return mContext; }*/
/*    EventType getType() { return mEventType; }*/
/*    void setContext(EventContext context) { memcpy(&mContext, &context, 128); }*/
/*    void setType(EventType type) { mEventType = type; }*/
/*private:*/
    /*EventContext mContext;*/
    /*EventType mEventType;*/
/*};*/




}
