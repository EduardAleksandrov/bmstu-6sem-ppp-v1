// OpenMP header
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void task1() {
    printf("Task 1 is running\n");
}

void task2() {
    printf("Task 2 is running\n");
}

void task3() {
    printf("Task 3 is running\n");
}


int main(int argc, char* argv[])
{
//---
    int nthreads, tid;

    // Begin of parallel region
    #pragma omp parallel private(nthreads, tid)
    {
        // Getting thread number
        tid = omp_get_thread_num();
        printf("Welcome to GFG from thread = %d\n",
               tid);

        if (tid == 0) {

            // Only master thread does this
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n",
                   nthreads);
        }
    }


//---
    omp_set_num_threads(4);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Section A – нить %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Section B – нить %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Section C – нить %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Section D – нить %d\n", omp_get_thread_num());
        }
    }  // здесь неявный barrier


//---
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                task1();
            }
            #pragma omp section
            {
                task2();
            }
            #pragma omp section
            {
                task3();
            }
        }
    }

//---
    const int N = 1000;
    double a[N], sum = 0.0;

    // Инициализируем массив
    for (int i = 0; i < N; i++) {
        a[i] = 1.0 * i;
    }

    // Установим желаемое число потоков (необязательно)
    omp_set_num_threads(4);

    // Параллельный for с редукцией суммы
    #pragma omp parallel for reduction(+:sum) schedule(static)
    for (int i = 0; i < N; i++) {
        sum += a[i];
    }

    printf("Sum = %f\n", sum);  

    sum = 0.0;
    int i;
    double local_sum;
        // Parallel region без автоматической редукции
    #pragma omp parallel \
        shared(a, N, sum) \
        private( /* перечислим переменные, приватными для каждой нити */         \
                  i, local_sum ) \
        num_threads(15)
    {
        local_sum = 0.0;  // приватная копия суммы для каждой нити

        // Распараллеливаем только цикл for, распределение как в schedule(static,1000)
        #pragma omp for schedule(static)
        for (i = 0; i < N; i++) {
            local_sum += a[i];
        }

        tid = omp_get_thread_num();
        printf("Welcome to GFG from thread = %d\n",tid);

        // По окончании цикла — атомарно прибавляем свою частичную сумму в общую
        #pragma omp atomic
        sum += local_sum;
    }  // здесь неявный barrier

    printf("Sum = %f\n", sum);
//---

    int x = 10; // Оригинальная переменная

    #pragma omp parallel firstprivate(x) // поток получает свою копию переменной, которая инициализируется значением переменной из родительского контекста.
    {
        // Каждый поток получает свою копию x, инициализированную значением 10
        x += omp_get_thread_num(); // Изменяем копию x
        printf("Thread %d: x = %d\n", omp_get_thread_num(), x);
    }

    // Значение x в родительском контексте остается неизменным
    printf("Original x after parallel region: %d\n", x);

    
    
    x = 0; // Оригинальная переменная

    #pragma omp parallel for lastprivate(x)
    for (int i = 0; i < 5; i++) {
        x = i; // Каждому потоку присваивается значение i
        printf("Thread %d: x = %d\n", omp_get_thread_num(), x);
    }

    // После завершения параллельного региона x будет равен 4
    printf("Last value of x after parallel region: %d\n", x);

//---



    return 0;
}