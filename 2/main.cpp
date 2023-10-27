//17. Найти в большом целочисленном массиве минимальный и максимальный элементы
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DEFAULT_THREAD_NUM 2

int* findMinMax(int* arr, size_t size) {
    if (arr == NULL || size == 0) {
        return NULL;
    }
    int* idxMinMax = new int[2]; // 0 idx is MIN, 1 idx is MAX
    int min = arr[0];
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
            idxMinMax[1] = i;
        }
        if (arr[i] < min) {
            min = arr[i];
            idxMinMax[0] = i;
        }
    }
    return idxMinMax;
}

typedef struct _threadMessage {
    int id;
    int* arrayPart;
    size_t arraySize;
    int* localMaxes;
    int* localMinimums;
} threadMessage;

void* threadWork(void* arg) {
    threadMessage* msg = (threadMessage*)arg;
    int id = msg->id;
    size_t size = msg->arraySize;
    int* arr = msg->arrayPart;

    int* found = findMinMax(arr, size);

    if (found == NULL) {
        std::cerr << "Error: Wrong array" << std::endl;
        exit(3);
    }
    
    msg->localMinimums[id] = arr[found[0]];
    msg->localMaxes[id] = arr[found[1]];

    delete[] found;

    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
        std::cerr << "Usage: ./lab <input_file> <threads_amount>" << std::endl;
        exit(1);
    }

    const char* filePath = argv[1];
    const int threadsAmount = (argc == 3) ? atoi(argv[2]) : DEFAULT_THREAD_NUM;

    std::cout << "Calculating on " << threadsAmount << " threads" << std::endl;

    // Opening input files
    std::ifstream fs(filePath);

    int n;
    fs >> n;

    //  Creating arrays
    int* array = new int[n];
    // Creating arrays for storing local min/max'es found by each thread
    int* localMaxes = new int[threadsAmount];
    int* localMinimums = new int[threadsAmount];

    // Reading array
    for (int i = 0; fs >> array[i]; i++);

    fs.close();

    // Thread List
    pthread_t* threadList = new pthread_t[threadsAmount];
    // Thread messages List
    threadMessage* msgList = new threadMessage[threadsAmount];

    clock_t begin = clock();

    int elemPerThread = n / threadsAmount;
    int elemRemain = n % threadsAmount;
    
    for (int i = 0; i < threadsAmount; i++) {
        bool lastThread = i == threadsAmount - 1;

        size_t left = i * elemPerThread;
        size_t right = left + elemPerThread - 1 + (lastThread ? elemRemain : 0);

        msgList[i] = (threadMessage) {
            .id            = i,
            .arrayPart     = array + left,
            .arraySize     = right - left + 1,
            .localMaxes    = localMaxes,
            .localMinimums = localMinimums,
            };

        // Creating threads
        if (pthread_create(&threadList[i], NULL, threadWork, static_cast<void*>(&msgList[i])) != 0) {
            std::cerr << "Failed to create thread << " << i << std::endl;
            exit(2);
        }
    }

    // Stopping threads
    for (int i = 0; i < threadsAmount; i++) {
        pthread_join(threadList[i], NULL);
    }

    int maxRes = INT_MIN;
    int minRes = INT_MAX;

    for (int i = 0; i < threadsAmount; i++) {
        if (localMaxes[i] > maxRes) {
            maxRes = localMaxes[i];
        }
        if (localMinimums[i] < minRes) {
            minRes = localMinimums[i];
        }
    }

    clock_t end = clock();

    std::cout << "MAX: " << maxRes << std::endl;
    std::cout << "MIN: " << minRes << std::endl;

    std::cout 
        << "Epalsed " 
        << static_cast<double>(end - begin) / CLOCKS_PER_SEC * 1000 
        << "ms" << std::endl;

    delete[] threadList;
    delete[] msgList;

    delete[] localMaxes;
    delete[] localMinimums;

    delete[] array;

    return 0;
}