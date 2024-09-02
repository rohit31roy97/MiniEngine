#pragma once

#include "core/Types.hpp"
#include "GLFW/glfw3.h"

// GLFW: Currently the default implementation for window generation on all platforms
// TODO: Reset to only work when GLFW preprocessor is set during compilation, once 
// platform dependent implementations are added in
#if (MINI_ENG_PLATFORM_APPLE == 1) || (MINI_ENG_PLATFORM_LINUX == 1) || (MINI_ENG_PLATFORM_WINDOWS == 1)

namespace MiniEngineCore {

MINI_API class WindowGLFW {
public:
    WindowGLFW(): mXSize(0), mYSize(0), mTitle(0), _window(0){}
    ~WindowGLFW() {}
    bool8 initWindow();
    bool8 createWindow(uint64 xsize, uint64 ysize, const char* title);
    bool8 keepOpen();
    bool8 destroyWindow();
    bool8 refreshWindowPerFrame();
private:
    GLFWwindow* _window;
    inline static bool8 GLFWInitialized = FALSE;
    uint64 mXSize;
    uint64 mYSize;
    char* mTitle;
    static void SetGLFWInitialized();
    static void UnsetGLFWInitialized();
};

using Window = WindowGLFW;

}

#endif
