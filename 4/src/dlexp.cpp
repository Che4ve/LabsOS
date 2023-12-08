#include "../include/dlexp.h"

float E1(int x) {
    return std::pow(1 + 1.0f / x, x);
}

// Функция для вычисления факториала
int64_t factorial(int64_t n) {
    return (n == 0 || n == 1) ? 1 : n * factorial(n - 1);
}

float E2(int x) {
    float sum = 0.0f;
    for (int n = 0; n <= x; n++) {
        sum += 1.0f / factorial(n);
    }
    return sum;
}