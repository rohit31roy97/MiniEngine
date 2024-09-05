#pragma once

#include "core/Types.hpp"

namespace MiniEngineCore {

enum class KeyInput {
    BACKSPACE, ENTER, TAB, SHIFT, CONTROL,
    PAUSE, CAPS, ESCAPE,CONVERT, NONCONVERT, ACCEPT, MODECHANGE,
    SPACE, PRIOR, NEXT, END, HOME, 
    LEFT,RIGHT, UP, DOWN, 
    SELECT, PRINT, EXECUTE, SNAPSHOT, INSERT, DELETE, HELP,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    LWIN, RWIN, APPS, SLEEP,
    NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8,
    NUMPAD9, MULTIPLY, ADD, SEPARATOR, SUBTRACT, DIVIDE, DECIMAL,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18,
    F19, F20, F21, F22, F23, F24, NUMLOCK, SCROLL, NUMPAD_EQUAL,
    LSHIFT, RSHIFT, LCONTROL, RCONTROL, LMENU, RMENU,
    SEMICOLON, PLUS, COMMA, MINUX, PERIOD, SLASH, GRAVE,
    MAX_KEYS
};

enum class ButtonInput {
    LEFT, RIGHT, MIDDLE, MAX_BUTTONS
};

MINI_API class KeyInputManager {
public:
    KeyInputManager();
    ~KeyInputManager();
    bool8 isDown(KeyInput key);
    bool8 isUp(KeyInput key);
    bool8 wasDown(KeyInput key);
    bool8 wasUp(KeyInput key);
    void processKey(KeyInput key, bool8 pressed);
    void updateStates();
private:
    bool8 mCurrentState[(uint64)KeyInput::MAX_KEYS];
    bool8 mPreviousState[(uint64)KeyInput::MAX_KEYS];
};

MINI_API class MouseInputManager {
public:
    MouseInputManager();
    ~MouseInputManager();
    bool8 isUp(ButtonInput button);
    bool8 wasUp(ButtonInput button);
    bool8 isDown(ButtonInput button);
    bool8 wasDown(ButtonInput button);
    void getCurrentLocation(int32* x, int32* y);
    void getPreviousLocation(int32* x, int32* y);
    void processButton(ButtonInput button, bool8 pressed);
    void processMouseMove(int32 x, int32 y);
    void processMouseWheel(int8 delta);
    void updateStates();
private:
    bool8 mCurrentState[(uint64)ButtonInput::MAX_BUTTONS];
    bool8 mPreviousState[(uint64)ButtonInput::MAX_BUTTONS];
    uint32 mCurrentX; uint32 mCurrentY;
    uint32 mPreviousX; uint32 mPreviousY;
    uint32 mScroll;
};

}

