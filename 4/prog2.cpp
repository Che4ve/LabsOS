// Вариант 33:	6	9

#include <iostream>
#include "dlfcn.h"

const char* DlExpPath = "../lib/libdlexp.dylib";
const char* DlSortPath = "../lib/libdlsort.dylib";

int main() {
    void* dlExpHandle = dlopen(DlExpPath, RTLD_LAZY);
    void* dlSortHandle = dlopen(DlSortPath, RTLD_LAZY);

    if (dlExpHandle == NULL || dlSortHandle == NULL) {
        std::cerr << "Failed to load dynamic libraries: " << dlerror() << std::endl;
    }

    typedef float (*EType)(int);
    EType E1 = (EType) dlsym(dlExpHandle, "E1");
    EType E2 = (EType) dlsym(dlExpHandle, "E2");

    typedef int* (*SortType)(int* array, int size);
    SortType bubbleSort = (SortType) dlsym(dlSortHandle, "bubbleSort");
    SortType hoareSort = (SortType) dlsym(dlSortHandle, "hoareSort");
    
    EType E = E1;
    SortType Sort = bubbleSort;

    char choice;
    std::cout << "Options:" << std::endl;
    std::cout << "'0' - switch realization\n" <<
                 "'1' - 1st contract\n" <<
                 "'2' - 2nd contract\n" <<
                 "'q' - Quit" << std::endl;
    do {
        std::cout << "Enter option: ";
        std::cin >> choice;
        switch (choice) {
            case '0':
                E = (E == E1) ? E2 : E1;
                Sort = (Sort == bubbleSort) ? hoareSort : bubbleSort;
                std::cout << "Functions realizations switched." << std::endl;
                break;

            case '1':
                int arg;
                std::cout << "\tEnter argument: ";
                std::cin >> arg;
                std::cout << "\tAnswer: " << E(arg) << std::endl;
                break;

            case '2': {
                int size;
                std::cout << "\tEnter size: ";
                std::cin >> size;
                int* array = new int[size];
                std::cout << "\tEnter array: ";
                for (int i = 0; i < size; ++i) {
                    std::cin >> array[i];
                }
                Sort(array, size);
                std::cout << "\tAnswer: ";
                for (int i = 0; i < size; ++i) {
                    std::cout << array[i] << " ";
                }
                std::cout << std::endl;
                delete[] array;
                break; 
            }
                
            case 'q':
                std::cout << "Bye!" << std::endl;
                break;

            default: 
                std::cout << "No such option " << std::endl;
                break;
        }
        
    } while (choice != 'q');
    
    return 0;
}