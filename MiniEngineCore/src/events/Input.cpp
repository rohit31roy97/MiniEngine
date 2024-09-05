#include "events/Input.hpp"
#include "core/Logging.hpp"

namespace MiniEngineCore {

/******** Defitinions for class KeyInputManger *******/

KeyInputManager::KeyInputManager() {
    for (uint32 i = 0; i < (int32)KeyInput::MAX_KEYS; i++) {
        mCurrentState[i] = 0;
        mPreviousState[i] = 0;
    }
    MLOG_INFO("KeyInputManger initialized");
}

KeyInputManager::~KeyInputManager() {
    MLOG_INFO("KeyInputManger deinitialized");
}

inline bool8 KeyInputManager::isDown(KeyInput key) {
    return (mCurrentState[(uint32)key] == 1);
}

inline bool8 KeyInputManager::isUp(KeyInput key) {
    return (mCurrentState[(uint32)key] == 0);
}

inline bool8 KeyInputManager::wasDown(KeyInput key) {
    return (mPreviousState[(uint32)key] == 1);
}

inline bool8 KeyInputManager::wasUp(KeyInput key) {
    return (mPreviousState[(uint32)key] == 0);
}

void KeyInputManager::processKey(KeyInput key, bool8 pressed) {
    if (mCurrentState[(uint32)key] != pressed) {
        mCurrentState[(uint32)key] = pressed;

        // TODO: Launch a KeyEvent to the event subsystem:
    }
}

void KeyInputManager::updateStates() {
    // TODO: Apply memcopy to copy over data from mCurrentState to mPreviousState
}

/******** Defitinions for class MouseInputManger *******/

MouseInputManager::MouseInputManager() {
    for (uint32 i = 0; i < (uint32)ButtonInput::MAX_BUTTONS; i++) {
        mCurrentState[i] = 0;
        mPreviousState[i] = 0;
        MLOG_INFO("MouseInputManager initialized");
    }
}

MouseInputManager::~MouseInputManager() {
        MLOG_INFO("MouseInputManager deinitialized");
}

inline bool8 MouseInputManager::isUp(ButtonInput button) {
    return mCurrentState[(uint32)button] == 0;
}

inline bool8 MouseInputManager::wasUp(ButtonInput button) {
    return mPreviousState[(uint32)button] == 0;
}

inline bool8 MouseInputManager::isDown(ButtonInput button) {
    return mCurrentState[(uint32)button] == 1;
}

inline bool8 MouseInputManager::wasDown(ButtonInput button) {
    return mPreviousState[(uint32)button] == 1;
}

inline void MouseInputManager::getCurrentLocation(int32* x, int32* y) {
    *x = mCurrentX;
    *y = mCurrentY;
}

inline void MouseInputManager::getPreviousLocation(int32* x, int32* y) {
    *x = mPreviousX;
    *y = mPreviousY;
}

void MouseInputManager::processButton(ButtonInput button, bool8 pressed) {
    if (mCurrentState[(uint32)button] != pressed) {
        mCurrentState[(uint32)button] = pressed;
        MLOG_DEBUG("Mouse button input %x %d", button, pressed);
        //TODO: Launch a ButtonEvent to event subsystem
    }
}

void MouseInputManager::processMouseMove(int32 x, int32 y) {
    if (mCurrentX != x ||  mCurrentY != y) {
        mCurrentX = x; mCurrentY = y;
        MLOG_DEBUG("Mouse button moved to %d %d", x, y);
        // TODO: Lauch MouseMoveEvent to event subsystem
    }
}

void MouseInputManager::processMouseWheel(int8 delta) {
    if (mScroll != delta) {
        mScroll = delta;
        // TODO: Lauch MouseScrollEvent to event subsystem
    }
}
void MouseInputManager::updateStates() {
    // TODO: Memcopy from mCurrentState to mPreviousState
}

}
