#pragma once

// Unsigned ints:
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

// Signed ints:
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

// Floating points:
typedef float float32;
typedef double float64;

// Booloean types:
typedef int bool32;
typedef char bool8;

#define TRUE 1
#define FALSE 0

// detfine static asserts based on compiler:
#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

// Check type sizes:
STATIC_ASSERT(sizeof(uint8) == 1, "uint8 should be of size 1 byte");
STATIC_ASSERT(sizeof(uint16) == 2, "uint8 should be of size 2 bytes");
STATIC_ASSERT(sizeof(uint32) == 4, "uint8 should be of size 4 bytes");
STATIC_ASSERT(sizeof(uint64) == 8, "uint8 should be of size 8 bytes");

STATIC_ASSERT(sizeof(int8) == 1, "int8 should be of size 1 byte");
STATIC_ASSERT(sizeof(int16) == 2, "int8 should be of size 2 bytes");
STATIC_ASSERT(sizeof(int32) == 4, "int8 should be of size 4 bytes");
STATIC_ASSERT(sizeof(int64) == 8, "int8 should be of size 8 bytes");

STATIC_ASSERT(sizeof(float32) == 4, "float32 should be of size 4 bytes");
STATIC_ASSERT(sizeof(float64) == 8, "float64 should be of size 8 bytes");

// Define macro flags based on platform:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define MINI_ENG_PLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "Windows must support 64-bit"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    #define MINI_ENG_PLATFORM_LINUX 1
#elif __APPLE__
    #define MINI_ENG_PLATFORM_APPLE 1
    #include <TargetConditionals.h>
#else
    #error "Platform not supported by MiniEngine"
#endif


// Define import / export calls for Windows DLL
#define MINI_API 
#ifdef MINI_ENG_EXPORT
    #ifdef _MSC_VER
        #define MINI_API __declspec(dllexport)
    #else
        #define MINI_API __attribute__((visibility("default")))
    #endif

    #ifdef _MSC_VER
        #define MINI_API __declspec(dllimport)
    #endif
#endif


