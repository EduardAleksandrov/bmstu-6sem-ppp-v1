#include <stdio.h>
#include <omp.h>

void vector_addition(float *a, float *b, float *result, int n) {
    #pragma omp simd
    for (int i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    int n = 1000;
    float a[1000], b[1000], result[1000];

    // Инициализация массивов
    for (int i = 0; i < n; i++) {
        a[i] = i * 1.0f;
        b[i] = i * 2.0f;
    }

    vector_addition(a, b, result, n);

    // Вывод результата
    for (int i = 0; i < 100; i++) {
        printf("result[%d] = %f\n", i, result[i]);
    }

    return 0;
}