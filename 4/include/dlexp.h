#pragma once
#include <iostream>
#include <cmath>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
    // Windows-specific declarations
    #ifdef DLIB_EXPORTS
        // This block is for building the DLL
        #define DLIB_API __declspec(dllexport)
    #else
        // This block is for using the DLL
        #define DLIB_API __declspec(dllimport)
    #endif
#else
    // Linux-specific declarations
    #define DLIB_API __attribute__((visibility("default")))
#endif

DLIB_API float E1(int x);

DLIB_API int64_t factorial(int64_t x);

DLIB_API float E2(int x);

#ifdef __cplusplus
}
#endif