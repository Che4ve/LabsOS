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

DLIB_API int* bubbleSort(int* array, int size);

DLIB_API int partition(int* array, int low, int high);

DLIB_API void quickSort(int* array, int low, int high);

DLIB_API int* hoareSort(int* array, int size);

#ifdef __cplusplus
}
#endif