#include "../include/dlsort.h"

int* bubbleSort(int* array, int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
                // Обмен значениями, если текущий элемент больше следующего
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return array;
}

// Функция для разделения массива на две части относительно опорного элемента
int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (array[j] <= pivot) {
            // Обмен значениями, если текущий элемент меньше или равен опорному
            ++i;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    // Обмен значениями для размещения опорного элемента в правильной позиции
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1;
}

// Функция для рекурсивной сортировки Хоара
void quickSort(int* array, int low, int high) {
    if (low < high) {
        // Находим опорный элемент
        int pivotIndex = partition(array, low, high);

        // Рекурсивно сортируем подмассивы до и после опорного элемента
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

int* hoareSort(int* array, int size) {
    quickSort(array, 0, size - 1);
    return array;
}
