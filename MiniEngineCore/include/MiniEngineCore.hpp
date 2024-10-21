#pragma once


#include "core/Types.hpp"
#include "core/Logging.hpp"
#include "core/Assertions.hpp"
#include "events/Event.hpp"
#include "platform/WindowGLFW.hpp"
#include "platform/WindowLinux.hpp"
#include "platform/WindowMacOS.hpp"
#include "platform/WindowWindows.hpp"

namespace MiniEngineCore {

enum class ApplicationPlatform {
    WINDOWS, MACOS, LINUX, GLFW
};

class Application {
public:
    Application();
    ~Application();

private:
    ApplicationPlatform mApplicationPlatform;
    Window mWindow;

};

}
