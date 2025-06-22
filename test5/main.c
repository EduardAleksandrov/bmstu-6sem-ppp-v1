#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void vector_addition(float *a, float *b, float *result, long long int n) {
    #pragma omp simd
    for (long long int i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    long long int n = 1500000000;
    float* a = (float*) malloc(sizeof(float) * n);
    float* b = (float*) malloc(sizeof(float) * n);
    float* result = (float*) malloc(sizeof(float) * n);

    // Инициализация массивов
    for (long long int i = 0; i < n; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    vector_addition(a, b, result, n);

    // Вывод результата
    for (int i = 0; i < 10; i++) {
        printf("result[%d] = %f\n", i, result[i]);
    }

    return 0;
}