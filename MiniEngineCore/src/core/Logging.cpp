#include "core/Types.hpp"
#include "core/Logging.hpp"
#include "core/Assertions.hpp"

#include <exception>
#include <iostream>

// Temporary not optimal solution (but so far pretty fast!)
#include <sstream>
#include <stdarg.h>


MINI_API bool8 MiniEngineCore::Logger::Initialize(void) {
    try {
        // TODO: Create Log File and maybe run some tests / generate logging queue
        ;
    } catch(std::exception e) {
        std::cerr << "An exception occured while setting up logging" << std::endl;
        std::cerr << e.what() << std::endl;
        return FALSE;
    }
    return TRUE;
}

MINI_API void MiniEngineCore::Logger::Deinitialize(void) {
    // TODO: Close log file and maybe run some tests // flush queued entries
}

MINI_API void MiniEngineCore::Logger::LogMessage(LogLevel level, const char* msg, ...) {
    bool8 is_error = level < LogLevel::WARN;
    const int16 max_message_size = 16000; // Currently max size = 16000 characters
    char message[max_message_size];
    memset(message, 0, max_message_size); // Initialize message with 0

    // Deal with VA_ARGS:
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(message, max_message_size, msg, arg_ptr);
    va_end(arg_ptr);

    // Append LogLevel to 
    std::string original_message(message);
    std::ostringstream final_message;
    std::string loglevelstr(LogLevelString[(int32)level]);
    final_message << loglevelstr << original_message << std::endl;

    // Print TODO: make this more platform specific output and optimal
    std::cout << final_message.str();
}

void MiniEngineCore::LogAssertionFail(const char* expression, const char* message, const char* filename, int32 line_no) {
    MiniEngineCore::Logger::LogMessage(                             \
        MiniEngineCore::LogLevel::FATAL,                            \
        "Assertion Failed: %s | Message: %s | File: %s, Line: %d",  \
        expression, message, filename, line_no                      \
    );
}
