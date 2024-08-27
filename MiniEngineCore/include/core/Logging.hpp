#include "Types.hpp"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Can be used to set LogLevel
#if MINI_ENG_RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif


namespace MiniEngineCore {

    enum class LogLevel {
        FATAL=0, ERROR=1, WARN=2, DEBUG=3, TRACE=4, INFO=5
    };

    class MINI_API Logger {
    public:
        static constexpr const char* LogLevelString[6] = {"[FATAL]:", "[ERROR]:", "[WARN] :", "[DEBUG]:", "[TRACE]:", "[INFO] :"}; 
        MINI_API static bool8 Initialize(void);
        MINI_API static void Deinitialize(void);
        MINI_API static void LogMessage(LogLevel level, const char* msg, ...);
    };
}

// Logging Macros (To be directly called):

// Log all FATAL 
#define MLOG_FATAL(message, ...) MiniEngineCore::Logger::LogMessage(MiniEngineCore::LogLevel::FATAL, message, ##__VA_ARGS__);

// Log all ERROR
#define MLOG_ERROR(message, ...) MiniEngineCore::Logger::LogMessage(MiniEngineCore::LogLevel::ERROR, message, ##__VA_ARGS__);

// Log WARN if enabled
#if LOG_WARN_ENABLED == 1
#define MLOG_WARN(message, ...) MiniEngineCore::Logger::LogMessage(MiniEngineCore::LogLevel::WARN, message, ##__VA_ARGS__);
#else
#define MLOG_WARN(message, ...)
#endif

// Log DEBUG if enabled
#if LOG_DEBUG_ENABLED == 1
#define MLOG_DEBUG(message, ...) MiniEngineCore::Logger::LogMessage(MiniEngineCore::LogLevel::DEBUG, message, ##__VA_ARGS__);
#else
#define MLOG_DEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define MLOG_TRACE(message, ...) MiniEngineCore::Logger::LogMessage(MiniEngineCore::LogLevel::TRACE, message, ##__VA_ARGS__);
#else
#define MLOG_TRACE(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define MLOG_INFO(message, ...) MiniEngineCore::Logger::LogMessage(MiniEngineCore::LogLevel::INFO, message, ##__VA_ARGS__);
#else
#define MLOG_INFO(message, ...)
#endif
