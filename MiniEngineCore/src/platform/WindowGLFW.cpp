#include "platform/WindowGLFW.hpp"
#include "core/Logging.hpp"
#include "core/Types.hpp"
#include <cstring>

// TODO: change to condition on flag for GLFW build, once platform specific implementations are in place
#if (MINI_ENG_PLATFORM_APPLE == 1) || (MINI_ENG_PLATFORM_LINUX == 1) || (MINI_ENG_PLATFORM_WINDOWS == 1)

namespace MiniEngineCore {

/* Implementaiton of class WindowGLFW: */
void WindowGLFW::SetGLFWInitialized() {
    GLFWInitialized = TRUE;
}

void WindowGLFW::UnsetGLFWInitialized() {
    GLFWInitialized = FALSE;
}

bool8 WindowGLFW::initWindow() {
    // If already initialized, do nothing:
    if (WindowGLFW::GLFWInitialized) {
        MLOG_WARN("GLFW already initialized, skipping!");
        return TRUE;
    }

    // Otherwise initialize GLFW (without OpenGL)
    const char* glfw_version = glfwGetVersionString();
    MLOG_INFO("GLFW Version: %s", glfw_version);
    if (!glfwInit()) {
        MLOG_FATAL("GLFW could not be initialized");
        return FALSE;
    }
    // Load GLFW without any Graphics backend
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    SetGLFWInitialized();
    MLOG_INFO("GLFW Initialized")
    return TRUE;
}

bool8 WindowGLFW::createWindow(uint64 xsize, uint64 ysize, const char* title) {
    mXSize = xsize;
    mYSize = ysize;
    mTitle = strdup(title);
    // GLFW create window:
    _window = glfwCreateWindow(mXSize, mYSize, mTitle, NULL, NULL);
    if (!_window) {
        MLOG_FATAL("GLFWwindow could not be created, shutting down Window subsystem.");
        destroyWindow();
        return FALSE;
    }
    else {
        return TRUE;
    }
}

bool8 WindowGLFW::refreshWindowPerFrame() {
    if (!WindowGLFW::GLFWInitialized || !_window) {
        MLOG_ERROR("GLFW not initialized, or window not created befor calling refresh, skipping!");
        return FALSE;
    }
    glfwSwapBuffers(_window);
    glfwPollEvents();
    return TRUE;
}

bool8 WindowGLFW::keepOpen() {
    return !glfwWindowShouldClose(_window);
}

bool8 WindowGLFW::destroyWindow() {
    if (_window != MINVALID_ADDRESS) {
        glfwDestroyWindow(_window);
        MLOG_INFO("GLFWwindow destroyed")
    }
    else {
        MLOG_WARN("GLFWwindow not created before calling destroy, skipping!");
    }
    if (WindowGLFW::GLFWInitialized == TRUE) {
        glfwTerminate();
        MLOG_INFO("GLFW terminated")
        WindowGLFW::UnsetGLFWInitialized();
    }
    else {
        MLOG_WARN("GLFW not initialized before calling terminate, skipping!");
    }
    return TRUE;
}

}

#endif
