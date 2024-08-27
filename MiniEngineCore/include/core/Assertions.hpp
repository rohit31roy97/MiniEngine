#pragma once

#include "Types.hpp"

// Disable assertions by overwriting below 
// TODO: Move such flags to be defined during build time:
#define MINI_ASSERTIONS_ENABLED


// If assertions enabled:
#ifdef MINI_ASSERTIONS_ENABLED

// Handle assertions if in MSVCC:
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

namespace MiniEngineCore {
    MINI_API void LogAssertionFail(const char* expression, const char* message, const char* filename, int32 line_no);
}

// Macros to redefine above function:
// Assert and break
#define MASSERT_STRICT(expression)                              \
{                                                               \
    if(expression) {                                            \
    } else {                                                    \
        MiniEngineCore::LogAssertionFail(#expression, "", __FILE__, __LINE__);  \
        debugBreak();                                           \
    }                                                           \
}

// Assert and break with message:
#define MASSERT_STRICT_MSG(expression, msg)                     \
{                                                               \
    if(expression) {                                            \
    } else {                                                    \
        MiniEngineCore::LogAssertionFail(#expression, msg, __FILE__, __LINE__); \
        debugBreak();                                           \
    }                                                           \
}

// Assert but do not break:
#define MASSERT(expression)                                     \
{                                                               \
    if(expression) {                                            \
    } else {                                                    \
        MiniEngineCore::LogAssertionFail(#expression, "", __FILE__, __LINE__);  \
    }                                                           \
}

// Assert but do not break with message:
#define MASSERT_MSG(expression, msg)                            \
{                                                               \
    if(expression) {                                            \
    } else {                                                    \
        MiniEngineCore::LogAssertionFail(#expression, msg, __FILE__, __LINE__); \
    }                                                           \
}

#else

// Assertions not enabled:
#define MASSERT_STRICT(expression)
#define MASSERT_STRICT_MSG(expression, msg)
#define MASSERT(expression)
#define MASSERT_MSG(expression, msg)

#endif
